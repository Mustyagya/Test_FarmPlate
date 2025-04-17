// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FarmPlotActor.generated.h"

UCLASS()
class TEST_FARMPLATE_API AFarmPlotActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFarmPlotActor();
	UFUNCTION(BlueprintCallable, Category = "Plot")
	void InitializePlot(FVector PlotLocation, FVector PlotSIze,  FVector InMeshOffset);
		

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
	UPROPERTY (VisibleAnywhere, BlueprintReadWrite,Category="Plot")
	class UBoxComponent* CollisionBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category="Plot")
	class UStaticMeshComponent* PlotMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category="Plot")
	FVector MeshOffset;
private:
	void UpdateMeshLocation();
};