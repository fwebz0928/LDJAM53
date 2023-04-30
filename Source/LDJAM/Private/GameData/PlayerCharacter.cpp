// Fill out your copyright notice in the Description page of Project Settings.


#include "GameData/PlayerCharacter.h"
#include "DeliveryPackages.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PlaceholderDeliveryVan = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Placeholder"));
	PlaceholderDeliveryVan->SetupAttachment(RootComponent);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 500.0f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->FieldOfView = 90.0f;

	ExhaustFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ExhaustFX"));
	ExhaustFX->SetupAttachment(RootComponent);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);

	MaxMoveSpeed = 50000.0f;
	MoveSpeedMultiplier = 1.1f;
	Health = 3;
	Score = 0;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	OnScoreUpdate.Broadcast(Score);
	OnHealthUpdate.Broadcast(Health);

	//Add Input Mapping Context
	PController = Cast<APlayerController>(Controller);
	if (PController)
	{
		Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PController->GetLocalPlayer());
		if (Subsystem)
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}


void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(ThrowRightAction, ETriggerEvent::Triggered, this, &APlayerCharacter::ThrowPackageRight);
		EnhancedInputComponent->BindAction(ThrowLeftAction, ETriggerEvent::Triggered, this, &APlayerCharacter::ThrowPackageLeft);
	}
}
FKey APlayerCharacter::GetActionPressedKeys(const TObjectPtr<UInputAction> Action) const
{
	if (Subsystem)
	{
		auto Keys = Subsystem->QueryKeysMappedToAction(Action);
		for (auto Key : Keys)
			if (PController->IsInputKeyDown(Key))
				return Key;
	}
	return FKey{};
}


void APlayerCharacter::ThrowPackageRight(const FInputActionValue& Value)
{
	if (bKeyPressed == false)
	{
		auto KeyDown = GetActionPressedKeys(ThrowRightAction);
		if (KeyDown == CurrentPopUpKey && bInZone)
		{
			bKeyPressed = true;
			IncreaseScore(1);
			ThrowDelivery();
		}
		else
			DamageHealth();
	}
}
void APlayerCharacter::DamageHealth()
{
	Health = FMath::Clamp(Health - 1, 0, 100);
	OnHealthUpdate.Broadcast(Health);
	AudioComponent->SetSound(LifeSFX);
	AudioComponent->Play();
	if (Health <= 0)
		OnPlayerDead.Broadcast();
}
void APlayerCharacter::ThrowPackageLeft()
{
	if (bKeyPressed == false)
	{
		auto KeyDown = GetActionPressedKeys(ThrowLeftAction);
		UE_LOG(LogTemp, Warning, TEXT("KeyPressed %s | Current Key %s"), *KeyDown.GetDisplayName().ToString(), *CurrentPopUpKey.GetDisplayName().ToString());
		if (KeyDown == CurrentPopUpKey && bInZone)
		{
			bKeyPressed = true;
			IncreaseScore(1);
			ThrowDelivery();
		}
		else
			DamageHealth();
	}
}

void APlayerCharacter::ThrowDelivery()
{
	FActorSpawnParameters SpawnParams;
	TObjectPtr<ADeliveryPackages> SpawnedPackage = GetWorld()->SpawnActor<ADeliveryPackages>(PackageClass, GetActorLocation(), FRotator::ZeroRotator, SpawnParams);

	// Calculate the velocity vector to reach the delivery location
	FVector LaunchDirection = (CurrentDeliveryLocation - GetActorLocation()).GetSafeNormal();
	FVector ProjectileVelocity = LaunchDirection * 1000.0f;
	ProjectileVelocity.Z += 500.0f;

	AudioComponent->SetSound(ThrowPackage);
	AudioComponent->Play();

	// Set the projectile's velocity and fire it
	SpawnedPackage->GetProjectileMovementComponent()->Velocity = ProjectileVelocity;
	SpawnedPackage->GetProjectileMovementComponent()->Activate();
	DrawDebugLine(GetWorld(), GetActorLocation(), CurrentDeliveryLocation, FColor::Yellow, true);
}

void APlayerCharacter::UpdateDeliveryData(FKey NewKey, FVector DeliveryLocation, bool bInCurrentZone)
{
	CurrentPopUpKey = NewKey;
	CurrentDeliveryLocation = DeliveryLocation;
	bInZone = bInCurrentZone;
}

void APlayerCharacter::IncreaseScore(const int IncreaseAmount)
{
	Score += IncreaseAmount;
	OnScoreUpdate.Broadcast(Score);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ScoreSFX, GetActorLocation());

	//When we hit a multiple of 10 increase the movement speed by 10
	if (Score % 2 == 0)
	{
		float WalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
		WalkSpeed = FMath::Clamp(WalkSpeed * MoveSpeedMultiplier, 0.0f, MaxMoveSpeed);
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
}
