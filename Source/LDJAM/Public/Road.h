// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "House.h"
#include "GameFramework/Actor.h"
#include "Road.generated.h"

class UBoxComponent;

UCLASS()
class LDJAM_API ARoad : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARoad();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FTransform GetAttachPointTransform() const;
	void SpawnHouses();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Destroyed() override;

private:
	TArray<FTransform> SpawnFoliageInArea(const FBoxSphereBounds& Bounds, int SpawnAmount) const;


	UPROPERTY(Category=Spawning, EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<AHouse> HouseClass;

	UPROPERTY()
	TObjectPtr<AHouse> SpawnedHouse;

	UPROPERTY(Category=Components, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> RoadMesh;
	UPROPERTY(Category=Components, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInstancedStaticMeshComponent> GrassMeshComponent;
	UPROPERTY(Category=Components, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInstancedStaticMeshComponent> FlowerMeshComponent;
	UPROPERTY(Category=Components, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> OverlapCollision;
	UPROPERTY(Category=Components, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> HouseSpawnAreaRight;
	UPROPERTY(Category=Components, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> HouseSpawnAreaLeft;
	UPROPERTY(Category=Components, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> FoliageSpawnAreaRight;
	UPROPERTY(Category=Components, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> FoliageSpawnAreaLeft;


	UPROPERTY(Category=Components, EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	int FoliageSpawnAmount;
};
