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
	FVector BoxSize = FVector(100.0f, 100.0f, 100.0f);
	//DrawDebugBox(GetWorld(), RandPoint, BoxSize, FColor::Blue, true);
	auto SpawnedHouse = GetWorld()->SpawnActor<AHouse>(HouseClass, RandPoint, SpawnRot);
	SpawnedHouse->bRightSide = RandBool;

	//Trace downward to detect the ground to make sure the house is always on the ground
	FHitResult HitResult;
	FVector EndLoc = GetActorLocation() + -GetActorUpVector() * 1000.0f;
	DrawDebugLine(GetWorld(), GetActorLocation(), EndLoc, FColor::Blue, true);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, SpawnedHouse->GetActorLocation(), EndLoc, ECC_Visibility, FCollisionQueryParams::DefaultQueryParam))
		SpawnedHouse->SetActorLocation(HitResult.ImpactPoint);
}
