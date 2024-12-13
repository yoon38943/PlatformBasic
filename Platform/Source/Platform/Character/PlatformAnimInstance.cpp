#include "PlatformAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UPlatformAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	APawn* Owner = TryGetPawnOwner();
	if (Owner == nullptr)
	{
		return;
	}
	UPawnMovementComponent* MovementComponent = Owner->GetMovementComponent();
	if (MovementComponent == nullptr)
	{
		return;
	}

	IsInAir = MovementComponent->IsFalling();
	FVector2D Velocity(MovementComponent->Velocity.X, MovementComponent->Velocity.Y);
	GroundSpeed = Velocity.Size();

	// Lean 연산
	CurrentRotation = Owner->GetActorRotation();
	//FRotator Delta = PreviousRotation - CurrentRotation;
	//Delta.Normalize();
	FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(PreviousRotation, CurrentRotation);	
	LeanAmount = FMath::FInterpTo(LeanAmount, Delta.Yaw, DeltaSeconds, 2.0f);
	PreviousRotation = CurrentRotation;

	IsMovementInput = false;
	if (Owner->GetLastMovementInputVector().Length() > 0.0f)
	{
		IsMovementInput = true;
	}
}