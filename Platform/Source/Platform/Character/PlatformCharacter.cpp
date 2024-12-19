#include "PlatformCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../ETC/HDebugMacros.h"


APlatformCharacter::APlatformCharacter()
{
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.25f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
}

void APlatformCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void APlatformCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateSmoothingCamera(DeltaTime);
}

void APlatformCharacter::Pause(const FInputActionValue& Value)
{
}

void APlatformCharacter::UpdateSmoothingCamera(float DeltaTime)
{
	FVector VStart = GetActorLocation();
	TArray<AActor*> ActorsToIgnore;

	FHitResult HitResult;
	bool IsHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), VStart, VStart + FVector(0.f, 0.f, 250.f),
			UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Camera), false, ActorsToIgnore,
			EDrawDebugTrace::None, HitResult, true);

	float DesiredTargetArmLenght = 300.f;
	if (IsHit == false)
	{
		DesiredTargetArmLenght = 600.f;
		if (GetMovementComponent()->IsFalling())
		{
			DesiredTargetArmLenght = 1000.f;
		}
	}

	float CurrentArmLength = FMath::FInterpTo(GetCameraBoom()->TargetArmLength, DesiredTargetArmLenght , DeltaTime, 1.f);
	GetCameraBoom()->TargetArmLength = CurrentArmLength;
}

void APlatformCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlatformCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (EndPlayReason == EEndPlayReason::Destroyed)
	{
	}
}

void APlatformCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 나중에 추가되는 입력만 처리
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
//h		EnhancedInputComponent->BindAction(CommandAction, ETriggerEvent::Triggered, this, &APlatformCharacter::RPCCommand);
	}
}