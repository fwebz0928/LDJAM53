// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "NiagaraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerCharacter.generated.h"

class UEnhancedInputLocalPlayerSubsystem;
class ADeliveryPackages;
class UInputComponent;
class UInputAction;
class UCameraComponent;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreUpdate, int, Score);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthUpdate, int, Health);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerDead);


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
	void UpdateDeliveryData(FKey NewKey, FVector DeliveryLocation, bool bInCurrentZone);
	UFUNCTION(BlueprintCallable)
	void DamageHealth();

	UFUNCTION(BlueprintCallable)
	void IncreaseScore(const int IncreaseAmount);

	UPROPERTY(BlueprintAssignable)
	FOnScoreUpdate OnScoreUpdate;
	UPROPERTY(BlueprintAssignable)
	FOnHealthUpdate OnHealthUpdate;
	UPROPERTY(BlueprintAssignable)
	FPlayerDead OnPlayerDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	FKey CurrentPopUpKey;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	bool bInZone;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	bool bKeyPressed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FKey GetActionPressedKeys(TObjectPtr<UInputAction> Action) const;

	void ThrowPackageRight(const FInputActionValue& Value);
	void ThrowPackageLeft();
	void ThrowDelivery();


	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> PlaceholderDeliveryVan;
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent;
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraComponent> ExhaustFX;
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UAudioComponent> AudioComponent;

	//Inputs
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ThrowRightAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ThrowLeftAction;
	UPROPERTY(BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> Subsystem;


	//Package Throwing
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameData|Delivery", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<ADeliveryPackages> PackageClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameData|Delivery", meta=(AllowPrivateAccess = "true"))
	float PackageThrowForce;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameData|Delivery", meta=(AllowPrivateAccess = "true"))
	float PackageLaunchForce;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "GameData", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<APlayerController> PController;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "GameData", meta=(AllowPrivateAccess = "true"))
	float MoveSpeedMultiplier;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "GameData", meta=(AllowPrivateAccess = "true"))
	float MaxMoveSpeed;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "GameData", meta=(AllowPrivateAccess = "true"))
	int Score;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "GameData", meta=(AllowPrivateAccess = "true"))
	int Health;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GameData", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> ScoreSFX;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GameData", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> LifeSFX;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GameData", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> ThrowPackage;


	FVector CurrentDeliveryLocation;
};
