// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "NiagaraComponent.h"
#include "PlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreUpdate, int, Score);

UCLASS()
class LDJAM_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void IncreaseScore(const int IncreaseAmount);

	UPROPERTY(BlueprintAssignable)
	FOnScoreUpdate OnScoreUpdate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> PlaceholderDeliveryVan;
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent;
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraComponent> ExhaustFX;


	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "GameData", meta=(AllowPrivateAccess = "true"))
	float MoveSpeedMultiplier;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "GameData", meta=(AllowPrivateAccess = "true"))
	float MaxMoveSpeed;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "GameData", meta=(AllowPrivateAccess = "true"))
	int Score;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "GameData", meta=(AllowPrivateAccess = "true"))
	int Health;
};
