// Fill out your copyright notice in the Description page of Project Settings.


#include "Road.h"
#include "Components/BoxComponent.h"
#include "Components/InstancedStaticMeshComponent.h"

// Sets default values
ARoad::ARoad()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RoadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RoadMesh"));
	RootComponent = RoadMesh;

	GrassMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("GrassInstanceMesh"));
	FlowerMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("FlowerInstanceMesh"));


	OverlapCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapCollision"));
	OverlapCollision->SetupAttachment(RootComponent);

	HouseSpawnAreaLeft = CreateDefaultSubobject<UBoxComponent>(TEXT("HouseSpawnLeft"));
	HouseSpawnAreaLeft->SetupAttachment(RootComponent);

	HouseSpawnAreaRight = CreateDefaultSubobject<UBoxComponent>(TEXT("HouseSpawnRight"));
	HouseSpawnAreaRight->SetupAttachment(RootComponent);

	FoliageSpawnAreaLeft = CreateDefaultSubobject<UBoxComponent>(TEXT("FoliageSpawnAreaLeft"));
	FoliageSpawnAreaLeft->SetupAttachment(RootComponent);


	FoliageSpawnAreaRight = CreateDefaultSubobject<UBoxComponent>(TEXT("FoliageSpawnAreaRight"));
	FoliageSpawnAreaRight->SetupAttachment(RootComponent);
}


FTransform ARoad::GetAttachPointTransform() const
{
	return RoadMesh->GetSocketTransform("AttachSocket");
}


void ARoad::SpawnHouses()
{
	//Get a random bool to decide if we should spawn on the left side or right side
	bool RandBool = FMath::RandBool();
	TObjectPtr<UBoxComponent> SpawnZone = nullptr;
	FRotator SpawnRot = FRotator::ZeroRotator;
	if (RandBool) // Right
	{
		SpawnZone = HouseSpawnAreaRight;
		SpawnRot = FRotator(0.0f, 180.0f, 0.0f);
	}
	else //Left
		SpawnZone = HouseSpawnAreaLeft;


	//Generate a random point inside the bounds
	FVector Origin = SpawnZone->Bounds.Origin;
	FVector BoxExtent = SpawnZone->Bounds.BoxExtent;
	FVector RandPoint = Origin + FVector(FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
	                                     FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
	                                     FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z));


	//Spawn the House 
	SpawnedHouse = GetWorld()->SpawnActor<AHouse>(HouseClass, RandPoint, SpawnRot);
	SpawnedHouse->bRightSide = RandBool;

	//Trace downward to detect the ground to make sure the house is always on the ground
	FHitResult HitResult;
	FVector HouseLoc = SpawnedHouse->GetActorLocation();
	FVector EndLoc = HouseLoc + -SpawnedHouse->GetActorUpVector() * 1000.0f;
	DrawDebugLine(GetWorld(), HouseLoc, EndLoc, FColor::Blue, true);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, SpawnedHouse->GetActorLocation(), EndLoc, ECC_Visibility, FCollisionQueryParams::DefaultQueryParam))
	{
		FVector NewLocation = FVector(HouseLoc.X, HouseLoc.Y, HitResult.ImpactPoint.Z);
		SpawnedHouse->SetActorLocation(NewLocation);
	}
}
void ARoad::OnConstruction(const FTransform& Transform)
{
	TArray<FTransform> FoliageTransforms;
	TArray<FTransform> FlowerTransforms;
	FoliageTransforms.Empty();
	FlowerTransforms.Empty();
	GrassMeshComponent->ClearInstances();
	FlowerMeshComponent->ClearInstances();

	FoliageTransforms += SpawnFoliageInArea(FoliageSpawnAreaLeft->Bounds, FoliageSpawnAmount);
	FoliageTransforms += SpawnFoliageInArea(FoliageSpawnAreaRight->Bounds, FoliageSpawnAmount);
	FlowerTransforms += SpawnFoliageInArea(FoliageSpawnAreaLeft->Bounds, 100);
	FlowerTransforms += SpawnFoliageInArea(FoliageSpawnAreaRight->Bounds, 100);

	FlowerMeshComponent->AddInstances(FlowerTransforms, false);
	GrassMeshComponent->AddInstances(FoliageTransforms, false);
}
void ARoad::Destroyed()
{
	if (SpawnedHouse)
		SpawnedHouse->Destroy();
}

TArray<FTransform> ARoad::SpawnFoliageInArea(const FBoxSphereBounds& Bounds, int SpawnAmount) const
{
	TArray<FTransform> OutTransforms;
	FVector Origin = Bounds.Origin;
	FVector BoxExtent = Bounds.BoxExtent;

	for (int i = 0; i < SpawnAmount; ++i)
	{
		FVector RandPoint = Origin + FVector(FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
		                                     FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
		                                     FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z));


		FQuat RandomRotation = FQuat::MakeFromEuler(FVector(0, 0, FMath::RandRange(0.f, 360.f)));
		RandomRotation.X = 0.0f;
		RandomRotation.Y = 0.0f;

		FTransform RandTransform;
		RandTransform.SetLocation(RandPoint);
		RandTransform.SetRotation(RandomRotation);
		OutTransforms.Add(RandTransform);
	}
	return OutTransforms;
}
