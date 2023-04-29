// Fill out your copyright notice in the Description page of Project Settings.


#include "GameData/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

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


	MaxMoveSpeed = 50000.0f;
	MoveSpeedMultiplier = 1.4f;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	OnScoreUpdate.Broadcast(Score);
}


void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
void APlayerCharacter::IncreaseScore(const int IncreaseAmount)
{
	Score += IncreaseAmount;
	OnScoreUpdate.Broadcast(Score);
	//When we hit a multiple of 10 increase the movement speed by 10
	if (Score % 10 == 0)
	{
		float WalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
		WalkSpeed = FMath::Clamp(WalkSpeed * MoveSpeedMultiplier, 0.0f, MaxMoveSpeed);
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
}
