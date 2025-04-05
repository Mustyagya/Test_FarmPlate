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
#include "StaticMeshAttributes.h"
//--
// Sets default values for this component's properties
// Конструктор
UBuildFarmActorComponent::UBuildFarmActorComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    bIsPlacing = false;
    CurrentCollisionBox = nullptr;
     bIsBoxRedy=false;
   // CurrentCollisionBox->bHiddenInGame = false; // Показывать объект даже в игре
   //  CurrentCollisionBox->SetVisibility(true);  // Включить видимость
}

// Инициализация компонента
void UBuildFarmActorComponent::BeginPlay()


{
    Super::BeginPlay();

    MyFarmPlotActorBPClass=LoadObject<UClass>(nullptr,TEXT("/Game/FarmPlatForm/MyFarmPlotActor.MyFarmPlotActor_C"));
    //MyFarmPlotActorBPClass=LoadObject<UClass>(nullptr,TEXT("Script/Test_FarmPlate.FarmPlotActor_C"));
    ///Script/Engine.Blueprint'/Game/FarmPlatForm/MyFarmPlotActor.MyFarmPlotActor'
    PreviousSize = FVector::ZeroVector;
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
        CurrentSize = FVector(250.0f, 250.0f, 150.0f);  // Начальные размеры бокса

        // Создаем коллизионный бокс
        FTransform BoxTransform;
        BoxTransform.SetLocation(InitialLocation);
        CurrentCollisionBox = NewObject<UBoxComponent>(GetOwner());
        if (CurrentCollisionBox)
        {
            CurrentCollisionBox->RegisterComponent();
            CurrentCollisionBox->SetWorldTransform(BoxTransform);
            CurrentCollisionBox->SetBoxExtent(CurrentSize / 4.0f);
            CurrentCollisionBox->SetHiddenInGame(false);
            CurrentCollisionBox->SetVisibility(true);
            CurrentCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

           //CurrentCollisionBox->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
        }

        bIsPlacing = true;  // Начинаем процесс установки участка
        bIsBoxRedy = false;
    }
}
//-----------------------------------------------------------------

//---
void UBuildFarmActorComponent::OnFinishPlacingFarmPlot()
{
    if (!bIsPlacing || !CurrentCollisionBox) return;
    bIsPlacing = false;
    Center = CurrentCollisionBox->GetComponentLocation();
    FVector HalfSize = CurrentCollisionBox->GetScaledBoxExtent();
    MinBounds = Center - HalfSize;
    MaxBounds = Center + HalfSize;
   // FVector Offset(5.0f, 5.0f, 0.0f);
    // Изменено: Генерация мелких боксов
    // Используем LastKnownSize для расчетов
    FVector CalculatedSize = LastKnowSize.IsNearlyZero() ? FVector(1000.0f, 1000.0f, 500.0f) : LastKnowSize;
//--------------------------------------------------
    // Используем внутренние координаты
     MinBounds = InternalBoundsMin;
     MaxBounds = InternalBoundsMax;
     //-------------------------------------------
     //новая строка Используем расширения границ
     float PaddingX_Min = StepX /  -1.35f; // Уменьшаем левую границу (например, -25.0f)
     float PaddingX_Max =  StepX / 0.99f; // Увеличиваем правую границу (например, +21.0f)
     float PaddingY_Min = StepY / -1.19f; // Уменьшаем нижнюю границу (например, -40.0f) верх
     float PaddingY_Max =  StepY / 0.99f; // Увеличиваем верхнюю границу (например, +30.0f) 
    /*FVector AdjustedMinBounds=InternalBoundsMin+FVector(21.0f,30.0f,0.0f);*/
     /*FVector AdjustedMaxBounds=InternalBoundsMax-FVector(-25.0f,-40.0f,0.0f);*/
     FVector AdjustedMinBounds = InternalBoundsMin - FVector(PaddingX_Min, PaddingY_Min, 0.0f); 
     FVector AdjustedMaxBounds = InternalBoundsMax + FVector(PaddingX_Max, PaddingY_Max, 0.0f);
     //  Дополнительная коррекция для нижнего правого угла
    UE_LOG(LogTemp, Warning, TEXT("Before Adjust: AdjustedMaxBounds.X=%f, AdjustedMinBounds.Y=%f"), AdjustedMaxBounds.X, AdjustedMinBounds.Y);
     AdjustedMaxBounds.X += StepX / 2222252.0f;  // Чуть увеличиваем вправо
     AdjustedMinBounds.Y -= StepY /  1152.0f;  // Чуть сдвигаем вниз
    UE_LOG(LogTemp, Warning, TEXT("After Adjust: AdjustedMaxBounds.X=%f, AdjustedMinBounds.Y=%f"), AdjustedMaxBounds.X, AdjustedMinBounds.Y);
    //--------------------------------------------
    MainBoxWidth = AdjustedMaxBounds.X - AdjustedMinBounds.X;
    MainBoxHeight =AdjustedMaxBounds.Y - AdjustedMinBounds.Y;

    int MaxStepsX = FMath::FloorToInt(MainBoxWidth / StepX);
    int MaxStepsY = FMath::FloorToInt(MainBoxHeight / StepY);
    UE_LOG(LogTemp, Warning, TEXT("MaxStepsX: %d, MaxStepsY: %d"), MaxStepsX, MaxStepsY);
    UE_LOG(LogTemp, Warning, TEXT("Перед обновлением StepX в OnFinishPlacingFarmPlot: %f"), StepX);
    //динамическая коррекция шагов 
    StepX=FMath::Clamp(MainBoxWidth/1.0f,40.0f,70.0f);// Минимальный шаг - 40, максимальный - 120
    StepY=FMath::Clamp(MainBoxHeight/1.0f,40.0f,70.0f);// Минимальный шаг - 40, максимальный - 80
    
 //-------------------------------------------------
    int MaxSteps = 10000;
    int StepCount = 1;
    FVector MinDebugBounds(FLT_MAX, FLT_MAX, FLT_MAX);
    FVector MaxDebugBounds(-FLT_MAX, -FLT_MAX, -FLT_MAX);
    //for (float X = MinBounds.X; X <= MaxBounds.X; X += StepX)
    for (float X = AdjustedMinBounds.X; X < AdjustedMaxBounds.X && StepCount < MaxSteps; X += StepX)
    {
        //for (float Y = MinBounds.Y; Y <= MaxBounds.Y; Y += StepY)
        for (float Y = AdjustedMinBounds.Y; Y < AdjustedMaxBounds.Y && StepCount < MaxSteps; Y += StepY)
        {
            FVector SmallBoxCenter(X, Y, Center.Z); //Старый варинат 
            //if (SmallBoxCenter.X > MaxBounds.X || SmallBoxCenter.Y > MaxBounds.Y)
              if (SmallBoxCenter.X < InternalBoundsMin.X || SmallBoxCenter.X > InternalBoundsMax.X ||
                  SmallBoxCenter.Y < InternalBoundsMin.Y || SmallBoxCenter.Y > InternalBoundsMax.Y)
               {
                    continue;
                }
            //FVector SmallBoxCenter=FVector (X,Y,0.0f).GridSnap(StepX)+Offset; // новый  
            // Округляем позицию мелкого бокса до ближайшей сетки с шагом StepX
             FVector SnappedPositionX =SmallBoxCenter.GridSnap(StepX); //старый вариант
             FVector SnappedPositionY =SmallBoxCenter.GridSnap(StepY);
                
                // Обновляем отладочные границы
            MinDebugBounds = FVector::Min(MinDebugBounds, SmallBoxCenter);
            MaxDebugBounds = FVector::Max(MaxDebugBounds, SmallBoxCenter); //старый вариант
             /*UE_LOG(LogTemp, Log, TEXT("SnappedPositionX: X=%f"), SnappedPositionX.X);
             UE_LOG(LogTemp, Log, TEXT("SnappedPositionY: Y=%f"), SnappedPositionY.Y);*/
            SpawnedLocation.Add(SmallBoxCenter);//Старый вариант
            FVector SmallBoxExtent(StepX / 2.0f, StepY / 2.0f, /*HalfSize.Z*/(MaxBounds.Z - MinBounds.Z) / 2.0f);
                if (SpawnedLocation.Num() > MaxSteps)
                {
                    break;
                }
            // Спавн маленького бокса
            //DrawDebugBox(GetWorld(), SmallBoxCenter, SmallBoxExtent, FColor::Red, true, -1.0f);

            // Спавн объекта (актора) в центре бокса
            if (MyFarmPlotActorBPClass)
            {
                FActorSpawnParameters SpawnParams;
                AFarmPlotActor* NewPlot = GetWorld()->SpawnActor<AFarmPlotActor>
                (MyFarmPlotActorBPClass, /*SnappedCenter*/SmallBoxCenter, FRotator::ZeroRotator, SpawnParams);
                if (NewPlot)
                {
                    NewPlot->InitializePlot( /*SnappedCenter*/ SmallBoxCenter, SmallBoxExtent, FVector(0.0f, 0.0f, -30.0f));
                }
            }
        }
    }
    // Применение Padding к MinDebugBounds и MaxDebugBounds
    //float Padding = -100.0f; // Отступ для MainBox
    MinDebugBounds -= FVector(100.0f,100.0f,0.0f/*Padding, Padding, Padding*/);
    MaxDebugBounds += FVector(100.0f,100.0f,0.0f/*Padding, Padding, Padding*/);
 // Добавляем отступы в финальных границах главного бокса
    //MinBounds += FVector(80.0f, 80.0f, 0.0f);
    //MaxBounds -= FVector(80.0f, 80.0f, 0.0f);

   // UE_LOG(LogTemp, Warning, TEXT("Final Bounds before applying: MinBounds: %s, MaxBounds: %s"), *MinBounds.ToString(), *MaxBounds.ToString());
    // Установка обновленных значений границ
    MinBounds = MinDebugBounds;
    MaxBounds = MaxDebugBounds;
     //UE_LOG(LogTemp, Warning, TEXT("Final MainBox Bounds: Min (%f, %f, %f), Max (%f, %f, %f)"),
       //     MinBounds.X, MinBounds.Y, MinBounds.Z, MaxBounds.X, MaxBounds.Y, MaxBounds.Z);
    
        //UE_LOG(LogTemp, Warning, TEXT("Debug Bounds for Small Boxes: Min (%f, %f, %f), Max (%f, %f, %f)"),
          //  MinDebugBounds.X, MinDebugBounds.Y, MinDebugBounds.Z, MaxDebugBounds.X, MaxDebugBounds.Y, MaxDebugBounds.Z);

    // Изменено: Таймер для удаления главного бокса
    //--------------------------------------------
    if (CurrentCollisionBox)
    {
        GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
        {
            if (CurrentCollisionBox)
            {
                // CurrentCollisionBox->DestroyComponent();
                // CurrentCollisionBox = nullptr;
                CurrentCollisionBox->SetHiddenInGame(false);
                CurrentCollisionBox->SetVisibility(true);
                bIsBoxRedy=true;
                
            }
        });
    }
    //--------------------------------------------
}
/*void UBuildFarmActorComponent::OnFinishPlacingFarmPlot()
{
    if (!bIsPlacing || !CurrentCollisionBox) return;

    bIsPlacing = false;

    // Новый расчёт центра главного бокса
    FVector MainBoxCenter = CurrentCollisionBox->GetComponentLocation();
    FVector MainBoxSize = CurrentCollisionBox->GetScaledBoxExtent() * 2.0f;

    // Динамическое смещение (10% от размера главного бокса)
    FVector Offset(MainBoxSize.X * 0.1f, MainBoxSize.Y * 0.1f, 0.0f);

    // Границы главного бокса
    this->MinBounds = MainBoxCenter - (MainBoxSize / 2.0f);
   this-> MaxBounds = MainBoxCenter + (MainBoxSize / 2.0f);

    // Словарь для уникальных позиций
    TSet<FVector> SpawnedLocations;

    // Цикл спавна мелких боксов
    for (float X = MinBounds.X; X <= MaxBounds.X; X += StepX)
    {
        for (float Y = MinBounds.Y; Y <= MaxBounds.Y; Y += StepY)
        {
            FVector SnappedCenter = FVector(X, Y, MainBoxCenter.Z).GridSnap(StepX) + Offset;

            FBox Bound(MinBounds,MaxBounds);

            // Проверка уникальности позиции и выхода за границы
            if (!Bound.IsInside(SnappedCenter) || SpawnedLocations.Contains(SnappedCenter))
            {
                UE_LOG(LogTemp, Warning, TEXT("Invalid position: X=%f, Y=%f"), SnappedCenter.X, SnappedCenter.Y);
                continue;
            }

            SpawnedLocations.Add(SnappedCenter);

            // Спавн объекта (актора)
            if (MyFarmPlotActorBPClass)
            {
                FActorSpawnParameters SpawnParams;
                AFarmPlotActor* NewPlot = GetWorld()->SpawnActor<AFarmPlotActor>(MyFarmPlotActorBPClass, SnappedCenter, FRotator::ZeroRotator, SpawnParams);

                if (NewPlot)
                {
                    NewPlot->InitializePlot(SnappedCenter, FVector(StepX / 2.0f, StepY / 2.0f, MainBoxSize.Z / 2.0f), FVector(0.0f, 0.0f, -30.0f));
                }
            }
        }
    }

    // Таймер для удаления главного бокса
    if (CurrentCollisionBox)
    {
        GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
        {
            if (CurrentCollisionBox)
            {
                CurrentCollisionBox->SetHiddenInGame(false);
                CurrentCollisionBox->SetVisibility(true);
            }
        });
    }
}*/
//---------------------------------------------------- конец части кода
//-------------------------------------------------------------------------------------------------

void UBuildFarmActorComponent::UpdateFarmPlotSize()
{
UE_LOG(LogTemp, Warning, TEXT("Before UpdateFarmPlotSize: InternalBoundsMin: %s, InternalBoundsMax: %s"),
 *InternalBoundsMin.ToString(), *InternalBoundsMax.ToString());
    //--
          FVector MaxSize = FVector(1000.0f, 1000.0f, 1000.0f);
        if (!LastHitResult.bBlockingHit || !bIsPlacing || !CurrentCollisionBox) return;
    //--
        FVector NewLocation = LastHitResult.ImpactPoint;
        FVector Delta = NewLocation - InitialLocation;
//--
   
    UE_LOG(LogTemp, Warning, TEXT("Before Change: InternalBoundsMin: %s, InternalBoundsMax: %s"),
        *InternalBoundsMin.ToString(), *InternalBoundsMax.ToString());
    /*FVector ExpandedSize = CurrentSize + FVector(80.0f, 80.0f, 0.0f);
    InternalBoundsMin = Center - (ExpandedSize / 2.0f);
    InternalBoundsMax = Center + (ExpandedSize / 2.0f);*/
    //----
        // Логика фиксации и увеличения осей
        if (FMath::Abs(Delta.X) > FMath::Abs(Delta.Y))
        {
            
            CurrentSize.Y = 250.0f;
            if (FMath::Abs(Delta.X) > 250.0f)
            {
                CurrentSize.Y += FMath::Abs(Delta.X) - 250.0f;
            }
            CurrentSize.X = FMath::Abs(Delta.X);
        }
        else
        {
           
            CurrentSize.X = 250.0f;
            if (FMath::Abs(Delta.Y) > 250.0f)
            {
                CurrentSize.X += FMath::Abs(Delta.Y) - 250.0f;
            }
            CurrentSize.Y = FMath::Abs(Delta.Y);
            //UE_LOG(LogTemp, Log, TEXT("Delta до расчета CurrentSize: X=%f, Y=%f"), Delta.X, Delta.Y);
          
        }
        
        // Обновление размеров главного бокса
            CurrentCollisionBox->SetBoxExtent(CurrentSize / 2.0f);
            Center = (InitialLocation + NewLocation) / 2.0f;
            Center.Z += 65.0f;
            CurrentCollisionBox->SetWorldLocation(Center);
            // Корректный расчет границ
            FVector HalfSize = CurrentSize / 2.0f;
            InternalBoundsMin=Center - HalfSize;
            InternalBoundsMax = Center + HalfSize;
        UE_LOG(LogTemp, Warning, TEXT("After Change: InternalBoundsMin: %s, InternalBoundsMax: %s"),
            *InternalBoundsMin.ToString(), *InternalBoundsMax.ToString());
   
    // Адаптивные шаги
    StepX = FMath::Clamp(MainBoxWidth / 1.0f, 40.0f, 70.0f);
    StepY = FMath::Clamp(MainBoxHeight / 1.0f, 40.0f, 70.0f);
 
    UE_LOG(LogTemp, Warning, TEXT("Center: %s"), *Center.ToString());
    UE_LOG(LogTemp, Warning, TEXT("CurrentSize: %s"), *CurrentSize.ToString());
    UE_LOG(LogTemp, Warning, TEXT("StepX: %f, StepY: %f"), StepX, StepY);
    UE_LOG(LogTemp, Warning, TEXT("InternalBoundsMin: %s, InternalBoundsMax: %s"), *InternalBoundsMin.ToString(), *InternalBoundsMax.ToString());
    
             //логика рядков  
                    /*if (FMath::IsNearlyEqual(CurrentSize.X, PreviousSize.X, 1.0f) &&
                        FMath::IsNearlyEqual(CurrentSize.Y, PreviousSize.Y, 1.0f))
                    {
                            //UE_LOG(LogTemp, Log, TEXT("StepX: %f, StepY: %f"), StepX, StepY);

                            if (FMath::Abs(Delta.Y) > FMath::Abs(Delta.X))
                            {
                                //StepY = 80.0f ; // Главная ось
                                 //StepX = 120.0f ; // Второстепенная ось
                               
                                 StepY = FMath::Max(CurrentSize.Y / 2.0f, 80.0f);
                                 StepX = FMath::Min(CurrentSize.X / 2.0f, 120.0f);
                            }
                                else
                                {
                                    //StepX = 120.0f ;
                                    //StepY = 80.0f ;
                                     StepX = FMath::Min(CurrentSize.X / 2.0f, 80.0f);
                                     StepY = FMath::Max(CurrentSize.Y / 2.0f, 120.0f);
                                }
                                // фексируем шаги в перделах доступных координат главного бокса
                               // StepX=FMath::Clamp(StepX,StepY,CurrentSize.X/2.0f);
                                //StepY=FMath::Clamp(StepY,StepX,CurrentSize.Y/2.0f);
                                //UE_LOG(LogTemp, Log, TEXT("InitialLocation: X=%f, Y=%f"), InitialLocation.X, InitialLocation.Y);
                                UE_LOG(LogTemp, Log, TEXT("Delta: X=%f, Y=%f"), Delta.X, Delta.Y);
                                UE_LOG(LogTemp, Log, TEXT("StepX=%f, StepY=%f"), StepX, StepY);
                            return;
                }*/
    if (CurrentSize.X < StepX || CurrentSize.Y < StepY)
    {
        //
        //   UE_LOG(LogTemp, Warning, TEXT("Размер главного бокса слишком мал для текущих шагов."));
        return;
    }
        // Увеличиваем размер главного бокса на 15 единиц по каждой оси X и Y
             CurrentSize.X += 50.0f;
             CurrentSize.Y += 50.0f;
        // FVector SnappedPositionX =.GridSnap(CurrentSize.X);
        // FVector SnappedPositionY =SmallBoxCenter.GridSnap(StepY);
        PreviousSize = CurrentSize;
       
        // Обновляем размер и расположение главного бокса
        /*CurrentCollisionBox->SetBoxExtent(CurrentSize / 2.0f);
         Center = (InitialLocation + NewLocation) / 2.0f;
        Center.Z += 35.0f;
        CurrentCollisionBox->SetWorldLocation(Center);*/
    // Вычисляем внутренние координаты
    /*FVector HalfSize = CurrentSize / 2.0f;
    InternalBoundsMin = Center - HalfSize;
    InternalBoundsMax = Center + HalfSize;*/
        // Отрисовка главного бокса
        DrawDebugBox(GetWorld(), Center, CurrentSize / 2.0f, FColor::Blue, false, 0.0f);
        // Проверка на минимальный размер бокса
        if (CurrentSize.X < 250.0f || CurrentSize.Y < 250.0f)
        {
            return;
        }
    // Вычисляем Delta для определения размеров
    //FVector Delta = MaxBounds - MinBounds;
    LastKnowSize=CurrentSize;
    /*FVector SnappedPosition;
    FVector MinDebugBounds(FLT_MAX, FLT_MAX, FLT_MAX);
    FVector MaxDebugBounds(-FLT_MAX, -FLT_MAX, -FLT_MAX);*/
    //for (float X = InitialLocation.X; X < InitialLocation.X + CurrentSize.X; X += StepX)
    //{
        //for (float Y = InitialLocation.Y; Y < InitialLocation.Y + CurrentSize.Y; Y += StepY)
        //{
          //  SnappedPosition = FVector(X, Y, InitialLocation.Z);
            //UE_LOG(LogTemp, Log, TEXT("Position: X=%f, Y=%f"), SnappedPosition.X, SnappedPosition.Y);
      //  }
    //}

    //for (float X = InternalBoundsMin.X; X < InternalBoundsMax.X; X += StepX)
    //{
    //for (float Y = InternalBoundsMin.Y; Y < InternalBoundsMax.Y; Y += StepY)
      //  {
           
        //FVector SmallBoxCenter(X, Y, Center.Z);
          //  MinDebugBounds = FVector::Min(MinDebugBounds, SmallBoxCenter);
            //MaxDebugBounds = FVector::Max(MaxDebugBounds, SmallBoxCenter);
        //}
    //}
    LastKnowSize = CurrentSize;
    CurrentCollisionBox->SetBoxExtent(CurrentSize / 2.0f);
    CurrentCollisionBox->SetWorldLocation(Center);
}