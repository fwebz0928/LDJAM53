// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DeliveryPackages.generated.h"

UCLASS()
class LDJAM_API ADeliveryPackages : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADeliveryPackages();
	void ThrowPackage(const float ThrowForce, const FVector& ThrowDirection, const float UpwardForce);

	UProjectileMovementComponent* GetProjectileMovementComponent() const { return ProjectileMovementComponent; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(Category=Components, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> DeliveryPackageMesh;
	UPROPERTY(Category=Components, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
};
