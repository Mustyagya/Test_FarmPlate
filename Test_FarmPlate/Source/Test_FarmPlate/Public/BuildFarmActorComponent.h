// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
//--
#include"DrawDebugHelpers.h"
#include"Kismet/GameplayStatics.h"
#include"Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/PlayerController.h"
//--
#include "FarmPlotActor.h"
#include "BuildFarmActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEST_FARMPLATE_API UBuildFarmActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuildFarmActorComponent();
protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void PerformLineTrace();  // Функция для выполнения трассировки луча
	void OnStartPlacingFarmPlot();  // Начало процесса установки бокса (первое нажатие ЛКМ)
	void OnFinishPlacingFarmPlot();  // Завершение процесса установки бокса (второе нажатие ЛКМ)
	void UpdateFarmPlotSize();  // Обновление размера коллизионного бокса

	UPROPERTY(EditAnywhere, Category = "FarmPlot")
	TSubclassOf<AFarmPlotActor> MyFarmPlotActor;

	// Хранит ссылку на Blueprint класс
	UPROPERTY(EditAnywhere, Category = "FarmPlot")
	TSubclassOf<class AFarmPlotActor> MyFarmPlotActorBPClass;

	FVector MaxBounds;
	FVector MinBounds;
	FVector InternalBoundsMax;
	FVector InternalBoundsMin;
	FVector Center;//пока просто обьявил тут
	float StepX;// new
	float StepY;//new
	float MainBoxWidth;
	float MainBoxHeight;
	bool bIsBoxRedy;
	
	

private:
	bool bIsPlacing;  // Флаг, определяющий процесс установки бокса
	FVector InitialLocation;  // Стартовая позиция бокса
	FVector CurrentSize;  // Текущий размер бокса
	FHitResult LastHitResult;  // Последний результат трассировки
	UBoxComponent* CurrentCollisionBox;  // Ссылка на текущий коллизионный бокс
	TSet<FVector> SpawnedLocation;//хранит уникальные координаты спувна
	FVector PreviousSize;//хранит предедущие координаты бокса

	FVector LastKnowSize;
	
	
};