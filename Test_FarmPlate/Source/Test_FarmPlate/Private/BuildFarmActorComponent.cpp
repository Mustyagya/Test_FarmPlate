// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildFarmActorComponent.h"

#include "MovieSceneTracksComponentTypes.h"
#include"GameFramework/Actor.h"
#include"Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include"Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/InputComponent.h"
#include "UObject/FastReferenceCollector.h"

//--
#include"FarmPlotActor.h"
//--
// Sets default values for this component's properties
// Конструктор
UBuildFarmActorComponent::UBuildFarmActorComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    bIsPlacing = false;
    CurrentCollisionBox = nullptr;
}

// Инициализация компонента
void UBuildFarmActorComponent::BeginPlay()
{
    Super::BeginPlay();

    MyFarmPlotActorBPClass=LoadObject<UClass>(nullptr,TEXT("/Game/FarmPlatForm/MyFarmPlotActor.MyFarmPlotActor_C"));
    //MyFarmPlotActorBPClass=LoadObject<UClass>(nullptr,TEXT("Script/Test_FarmPlate.FarmPlotActor_C"));
    ///Script/Engine.Blueprint'/Game/FarmPlatForm/MyFarmPlotActor.MyFarmPlotActor'
    
    // Получаем PlayerController и связываем действия с ЛКМ
    if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        if (PC->InputComponent)
        {
            PC->InputComponent->BindAction("PlaceFarmPlot", IE_Pressed, this, &UBuildFarmActorComponent::OnStartPlacingFarmPlot);
            PC->InputComponent->BindAction("PlaceFarmPlot", IE_Released, this, &UBuildFarmActorComponent::OnFinishPlacingFarmPlot);
        }
    }
}

// Функция, вызываемая каждый тик
void UBuildFarmActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    PerformLineTrace();  // Выполняем трассировку луча каждый кадр

    if (bIsPlacing)
    {
        UpdateFarmPlotSize();  // Обновляем размер бокса, если игрок еще выбирает размеры
    }
}

// Трассировка луча
void UBuildFarmActorComponent::PerformLineTrace()
{
    AActor* Owner = GetOwner();
    if (!Owner) return;

    // Получаем компонент камеры
    UCameraComponent* CameraComponent = Owner->FindComponentByClass<UCameraComponent>();
    if (!CameraComponent) return;

    // Стартовая точка и направление трассировки
    FVector Start = CameraComponent->GetComponentLocation();
    FVector ForwardVector = CameraComponent->GetForwardVector();
    FVector End = Start + (ForwardVector * 1000.0f);

    FCollisionQueryParams TraceParams;
    TraceParams.AddIgnoredActor(Owner);

    // Выполняем трассировку
    bool bHit = GetWorld()->LineTraceSingleByChannel(LastHitResult, Start, End, ECC_Visibility, TraceParams);

    // Отображаем результат трассировки
    if (bHit)
    {
        DrawDebugLine(GetWorld(), Start, LastHitResult.ImpactPoint, FColor::Green, false, -1, 0, 1.0f);
    }
    else
    {
        DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, -1, 0, 1.0f);
    }
}

// Начало установки участка (первое нажатие ЛКМ)
void UBuildFarmActorComponent::OnStartPlacingFarmPlot()
{
    if (LastHitResult.bBlockingHit)
    {
        InitialLocation = LastHitResult.ImpactPoint;
        CurrentSize = FVector(150.0f, 150.0f, 120.0f);  // Начальные размеры бокса

        // Создаем коллизионный бокс
        FTransform BoxTransform;
        BoxTransform.SetLocation(InitialLocation);
        CurrentCollisionBox = NewObject<UBoxComponent>(GetOwner());
        if (CurrentCollisionBox)
        {
            CurrentCollisionBox->RegisterComponent();
            CurrentCollisionBox->SetWorldTransform(BoxTransform);
            CurrentCollisionBox->SetBoxExtent(CurrentSize / 2.0f);
            CurrentCollisionBox->SetHiddenInGame(false);
            CurrentCollisionBox->SetVisibility(true);
            CurrentCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

           //CurrentCollisionBox->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
        }

        bIsPlacing = true;  // Начинаем процесс установки участка
    }
}

// Завершение установки участка (второе нажатие ЛКМ)
void UBuildFarmActorComponent::OnFinishPlacingFarmPlot()
{
    if (bIsPlacing)
    {
        bIsPlacing = false;  // Завершаем процесс установки участка

        if (CurrentCollisionBox)
        {
            // Финализируем размер коллизионного бокса
            CurrentCollisionBox->SetBoxExtent(CurrentSize / 2.0f);
        }
    }
}


//--------------------------------------------------------------------------------------------------------------
/*
//аздиление основного бокса на мелкие с отступами и есть код на добавления актра в нутри мелкого бокса но это тоже не вариант НО ОН РАБОЧИЙ НЕ ТРОГАТЬ!!!!! 
void UBuildFarmActorComponent::UpdateFarmPlotSize()
{
    if (!LastHitResult.bBlockingHit || !bIsPlacing || !CurrentCollisionBox) return;

    FVector NewLocation = LastHitResult.ImpactPoint;
    FVector Delta = NewLocation - InitialLocation;

    // Логика фиксации и увеличения осей
    if (FMath::Abs(Delta.X) > FMath::Abs(Delta.Y)) 
    {
        // Двигаем больше по X, фиксируем Y
        CurrentSize.Y = 150.0f;

        // Если X превысил фиксированное значение, увеличиваем Y
        if (FMath::Abs(Delta.X) > 150.0f)
        {
            CurrentSize.Y += FMath::Abs(Delta.X) - 150.0f;
        }

        CurrentSize.X = FMath::Abs(Delta.X);  // Продолжаем увеличивать X
    }
    else 
    {
        // Двигаем больше по Y, фиксируем X
        CurrentSize.X = 150.0f;

        // Если Y превысил фиксированное значение, увеличиваем X
        if (FMath::Abs(Delta.Y) > 150.0f)
        {
            CurrentSize.X += FMath::Abs(Delta.Y) - 150.0f;
        }

        CurrentSize.Y = FMath::Abs(Delta.Y);  // Продолжаем увеличивать Y
    }

    // Обновляем размеры и расположение главного коллизионного бокса
    CurrentCollisionBox->SetBoxExtent(CurrentSize / 2.0f);
    FVector Center = (InitialLocation + NewLocation) / 2.0f;
    CurrentCollisionBox->SetWorldLocation(Center);

    // Отрисовка главного бокса для наглядности
    DrawDebugBox(GetWorld(), Center, CurrentSize / 2.0f, FColor::Blue, false, 0.0f);


    
    // Разделение на мелкие боксы 150x150, если X и Y кратны 150
    FVector MinBounds = Center - (CurrentSize / 2.0f); // Нижняя левая точка главного бокса
    FVector MaxBounds = Center + (CurrentSize / 2.0f); // Верхняя правая точка главного бокса

    // Определяем шаги с отступами
    float StepX = 150.0f;
    float StepY = 150.0f;

    // Главная ось — добавляем 50 см отступ, меньшая — 20 см
    if (FMath::Abs(Delta.Y) > FMath::Abs(Delta.X))
    {
        StepY += 50.0f; // Главная ось Y — отступ 50 см
        StepX += 20.0f; // Меньшая ось X — отступ 20 см
    }
    else
    {
        StepX += 50.0f; // Главная ось X — отступ 50 см
        StepY += 20.0f; // Меньшая ось Y — отступ 20 см
    }
    
    for (float x = MinBounds.X; x <= MaxBounds.X; x += StepX)
    {
        for (float y = MinBounds.Y; y <= MaxBounds.Y; y += StepY)
        {
            // Создаем координаты для каждого маленького бокса
            FVector SmallBoxCenter(x + StepX/2, y + StepY/2, Center.Z);  // Центр маленького бокса
            FVector SmallBoxExtent(150.0f / 2.0f, 150.0f / 2.0f, CurrentSize.Z / 2.0f);  // Размеры маленького бокса
            
            // Отрисовываем маленький бокс
            DrawDebugBox(GetWorld(), SmallBoxCenter, SmallBoxExtent, FColor::Red, false, 0.0f);
        }
    }

    // Отображение координат на экране для проверки
    FString CoordinateText = FString::Printf(TEXT("X: %f, Y: %f"), CurrentSize.X, CurrentSize.Y);
    DrawDebugString(GetWorld(), Center, CoordinateText, nullptr, FColor::White, 0.0f, true);
}
*/
//----------------------------------------------------------------------------------------------------------------------------------



//Здесь код рабочий с расположение  БП-дочернего класса актера

/*
void UBuildFarmActorComponent::UpdateFarmPlotSize()
{
    if(!LastHitResult.bBlockingHit || !bIsPlacing ||!CurrentCollisionBox) return;
    FVector NewLocation = LastHitResult.ImpactPoint;
    FVector Delta=NewLocation - InitialLocation;

    //Логика фиксации и увеличения осей
    if(FMath::Abs(Delta.X) > FMath::Abs(Delta.Y))
    {
        //двигатся по оси Х, фиксируем Y
        CurrentSize.Y=150.0f;
        if(FMath::Abs(Delta.X)>150.0f)
        {
            CurrentSize.Y +=FMath::Abs(Delta.X)-150.0f;
            
        }
        CurrentSize.X=FMath::Abs(Delta.X);
    }
    else
    {
        CurrentSize.X=150.0f;
        if(FMath::Abs(Delta.Y)>150.0f)
        {
            CurrentSize.X+=FMath::Abs(Delta.Y)-150.0f;
        }
        CurrentSize.Y=FMath::Abs(Delta.Y);
    }
//обновляем размер и расположение главного бокса
    CurrentCollisionBox->SetBoxExtent(CurrentSize/2.0f);
    FVector Center =(InitialLocation+NewLocation)/2.0f

    ;
    Center.Z+=67.0f;
    CurrentCollisionBox->SetWorldLocation(Center);
    
    // Отрисовка главного бокса для наглядности
    DrawDebugBox(GetWorld(), Center, CurrentSize / 2.0f, FColor::Blue, false, 0.0f);
    
    //орпедиление границы
    FVector MinBounds=Center-(CurrentSize/2.0f);
    FVector MaxBounds=Center+(CurrentSize/2.0f);

    //определяем шапги с отступами
    float StepX=150.0f;
    float StepY=150.0f;
    //отступы для главной и второстепенной осей в огроде
    if (FMath::Abs(Delta.Y)>FMath::Abs(Delta.X))
    {
        StepY+=50.0f;//главная рядка
        StepX+=20.0f;//второстепенная ряд
    }
    else
    {
        StepX+=50.0f;
        StepY+=20.0f;
    }
for(float x= MinBounds.X; x<=MaxBounds.X; x+=StepX)
{
    for(float y= MinBounds.Y; y<=MaxBounds.Y; y+=StepY)
    {

        FVector SmallBoxCenter(x + StepX / 2, y + StepY / 2, Center.Z);
        FVector SmallBoxExtent(150.0f / 2.0f, 150.0f / 2.0f, CurrentSize.Z / 2.0f);

        // Используем класс дочернего Blueprint'а вместо родительского C++ класса
        FActorSpawnParameters SpawnParams;
        AFarmPlotActor* NewPlot = GetWorld()->SpawnActor<AFarmPlotActor>(MyFarmPlotActorBPClass, SmallBoxCenter, FRotator::ZeroRotator, SpawnParams);
        FVector InMeshOffset = FVector(0.f, 0.f, -50.f);
        if (NewPlot)
        {
            NewPlot->InitializePlot(SmallBoxCenter, SmallBoxExtent,InMeshOffset);
          
        }
            
        DrawDebugBox(GetWorld(), SmallBoxCenter, SmallBoxExtent, FColor::Red, false, 0.0f);


        //FVector SmallPlotCenter(x+StepX/2, y+StepY/2,Center.Z);
        
            //спавн актора для на участок кавадрата
        //FActorSpawnParameters SpawnParams;
        //AFarmPlotActor*NewPlot =GetWorld()->SpawnActor<AFarmPlotActor>(AFarmPlotActor::StaticClass(), SmallPlotCenter, FRotator::ZeroRotator, SpawnParams);
       
       // AFarmPlotActor* NewPlot =GetWorld()->SpawnActor<AFarmPlotActor>(MyFarmPlotActor, AdjustedCenter, FRotator::ZeroRotator,SpawnParams);
        //if (NewPlot)
        //{
            
           // FVector PlotSize(150.0f, 150.0f, 120.0f);
            //NewPlot->InitializePlot(SmallPlotCenter, PlotSize,FVector(0.0f, 0.0f, 0.0f));
        //}
    }
}

    // Отображение координат на экране для проверки
    FString CoordinateText = FString::Printf(TEXT("X: %f, Y: %f"), CurrentSize.X, CurrentSize.Y);
    DrawDebugString(GetWorld(), Center, CoordinateText, nullptr, FColor::White, 0.0f, true);

        
}
*/

//-------------------------------------------------------------------------------------------------

//Попробуем разделить функцию на то чтобы тут создавался только главный бокс и внутри него были тольок разделение на грядки
void UBuildFarmActorComponent::UpdateFarmPlotSize()
{
    if (!LastHitResult.bBlockingHit|| !bIsPlacing|| !CurrentCollisionBox) return;
    FVector NewLocation = LastHitResult.ImpactPoint;
    FVector Delta=NewLocation - InitialLocation;

    //Логика для расчета главного бокса по осям
    if (FMath::Abs(Delta.X)>FMath::Abs(Delta.Y))
    {
        //двигаемся по оис Y, фексируем Y
        CurrentSize.Y=150.0f;
        if(FMath::Abs(Delta.X)>150.0)
        {
            CurrentSize.Y+=FMath::Abs(Delta.X)-150.0f;
        }
        CurrentSize.X=FMath::Abs(Delta.X);
    }
    else
    {
        // Двигаться по оси Y, фиксируем X
    }

    
}

    