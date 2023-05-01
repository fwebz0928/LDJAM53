// Fill out your copyright notice in the Description page of Project Settings.


#include "House.h"

#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
AHouse::AHouse()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	HouseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HouseMesh"));
	RootComponent = HouseMesh;

	DeliveryLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("DeliverLocation"));
	DeliveryLocation->SetupAttachment(RootComponent);

	ChimneyFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ChimneyFX"));
	ChimneyFX->SetupAttachment(RootComponent);

	TriggerBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);

	TriggerZone = CreateDefaultSubobject<UBoxComponent>(TEXT("WidgetTriggerZone"));
	TriggerZone->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AHouse::BeginPlay()
{
	Super::BeginPlay();

	//Set a random mesh for the house
	int RandIndex = FMath::RandRange(0, HouseMeshes.Num() - 1);
	HouseMesh->SetStaticMesh(HouseMeshes[RandIndex]);

	//Update the fx location of the meshes chimney
	FVector ChimneyLocation = HouseMesh->GetSocketLocation("FXSocket");
	ChimneyFX->SetRelativeLocation(ChimneyLocation);
}
FKey AHouse::GetRandomKey()
{
	if (PCharacter == nullptr) return FKey{};
	int RandIndex;
	if (bRightSide)
	{
		RandIndex = FMath::RandRange(0, RightSideKeys.Num() - 1);
		return RightSideKeys[RandIndex];
	}
	RandIndex = FMath::RandRange(0, LeftSideKeys.Num() - 1);
	return LeftSideKeys[RandIndex];
}
