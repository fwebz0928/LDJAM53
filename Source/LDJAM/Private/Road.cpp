// Fill out your copyright notice in the Description page of Project Settings.


#include "Road.h"

#include "Components/BoxComponent.h"

// Sets default values
ARoad::ARoad()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RoadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RoadMesh"));
	RootComponent = RoadMesh;

	OverlapCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapCollision"));
	OverlapCollision->SetupAttachment(RootComponent);

	HouseSpawnAreaLeft = CreateDefaultSubobject<UBoxComponent>(TEXT("HouseSpawnLeft"));
	HouseSpawnAreaLeft->SetupAttachment(RootComponent);

	HouseSpawnAreaRight = CreateDefaultSubobject<UBoxComponent>(TEXT("HouseSpawnRight"));
	HouseSpawnAreaRight->SetupAttachment(RootComponent);
}


FTransform ARoad::GetAttachPointTransform() const
{
	return RoadMesh->GetSocketTransform("AttachSocket");
}


void ARoad::SpawnHouses()
{
	//Get a random bool to decide if we should spawn on the left side or right side
	bool RandBool = FMath::RandBool();
	TObjectPtr<UBoxComponent> SpawnZone = RandBool ? HouseSpawnAreaLeft : HouseSpawnAreaRight;

	FVector Origin = SpawnZone->Bounds.Origin;
	FVector BoxExtent = SpawnZone->Bounds.BoxExtent;

	FVector RandPoint = Origin + FVector(FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
	                                     FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
	                                     FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z));


	FVector BoxSize = FVector(100.0f, 100.0f, 100.0f);
	DrawDebugBox(GetWorld(), RandPoint, BoxSize, FColor::Blue, true);
}
