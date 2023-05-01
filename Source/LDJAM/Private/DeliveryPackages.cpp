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
	ProjectileMovementComponent->SetUpdatedComponent(DeliveryPackageMesh);
	ProjectileMovementComponent->bShouldBounce = false;
	ProjectileMovementComponent->InitialSpeed = 0.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->SetActive(false);
}


// Called when the game starts or when spawned
void ADeliveryPackages::BeginPlay()
{
	Super::BeginPlay();
}

void ADeliveryPackages::ThrowPackage(const float ThrowForce, const FVector& ThrowDirection, const float UpwardForce)
{
	// Calculate the velocity needed to throw the grenade in an arc trajectory
	FVector Velocity = ThrowDirection * ThrowForce;
	Velocity.Z += UpwardForce; // Add some upward force to make it arc

	// Apply the velocity to the ProjectileMovementComponent
	ProjectileMovementComponent->SetVelocityInLocalSpace(Velocity);
	// Start moving the grenade
	ProjectileMovementComponent->SetActive(true);
}
