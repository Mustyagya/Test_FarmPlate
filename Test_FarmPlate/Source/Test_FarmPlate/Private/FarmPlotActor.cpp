// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmPlotActor.h"

#include "MovieSceneSequenceID.h"
#include "Components//BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include"Kismet\GameplayStatics.h"

// Sets default values
AFarmPlotActor::AFarmPlotActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox=CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent=CollisionBox;
	CollisionBox->bHiddenInGame = false; // Показывать объект даже в игре
	CollisionBox->SetVisibility(true);  // Включить видимость

	
	PlotMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlotMesh"));
	PlotMesh->SetupAttachment(RootComponent);//подключаем к корневому(главноему обьенкту)
	PlotMesh->SetVisibility(true);

	AutoReceiveInput = EAutoReceiveInput::Player0;
	
}


// Called when the game starts or when spawned
void AFarmPlotActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFarmPlotActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AFarmPlotActor::InitializePlot(FVector PlotLocation, FVector PlotSIze ,FVector InMeshOffset)
{
	SetActorLocation(PlotLocation);

	if (CollisionBox)
	{
		CollisionBox->SetBoxExtent(PlotSIze/2.0f);
	}
	
	
	MeshOffset=InMeshOffset;
	PlotMesh->SetRelativeLocation( MeshOffset);
	// Проверяем, чтобы PlotMesh оставался внутри главного CollisionBox
	
	UpdateMeshLocation();
}

void AFarmPlotActor::SetHighlight(bool bHighlight)
{
	if (!PlotMesh || !NormalMaterial || !HighlightMaterial) return;

	UMaterialInterface* NewMaterial = bHighlight ? HighlightMaterial : NormalMaterial;
	PlotMesh->SetMaterial(0, NewMaterial);
}


void AFarmPlotActor::UpdateMeshLocation()
{
	if (PlotMesh)
	{
		PlotMesh->SetRelativeLocation(MeshOffset); 
		PlotMesh->SetVisibility(true);
		PlotMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		UE_LOG(LogTemp, Log, TEXT("PlotMesh is now visible and has collision enabled."));
	}
}
