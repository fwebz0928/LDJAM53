// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameData/PlayerCharacter.h"
#include "GameFramework/Actor.h"
#include "House.generated.h"

class UBoxComponent;
class UArrowComponent;

UCLASS()
class LDJAM_API AHouse : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHouse();

	bool bRightSide;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	FKey GetRandomKey();

private:
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> HouseMesh;
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UArrowComponent> DeliveryLocation;
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraComponent> ChimneyFX;

	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> TriggerBox;
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> TriggerZone;

	UPROPERTY(Category=HouseData, EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<APlayerCharacter> PCharacter;
	UPROPERTY(Category=HouseData, EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TArray<FKey> RightSideKeys;
	UPROPERTY(Category=HouseData, EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TArray<FKey> LeftSideKeys;
	UPROPERTY(Category=HouseData, EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UStaticMesh>> HouseMeshes;

};
