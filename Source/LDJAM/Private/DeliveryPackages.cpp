// Fill out your copyright notice in the Description page of Project Settings.


#include "DeliveryPackages.h"

// Sets default values
ADeliveryPackages::ADeliveryPackages()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DeliveryPackageMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PackageMesh"));
	RootComponent = DeliveryPackageMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));
	ProjectileMovementComponent->InitialSpeed =300.0f;
	
}

// Called when the game starts or when spawned
void ADeliveryPackages::BeginPlay()
{
	Super::BeginPlay();
}
