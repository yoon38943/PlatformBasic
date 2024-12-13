#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlatformAnimInstance.generated.h"


UCLASS()
class PLATFORM_API UPlatformAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite)
	bool IsInAir;
	UPROPERTY(BlueprintReadWrite)
	bool IsMovementInput;
	UPROPERTY(BlueprintReadWrite)
	float GroundSpeed;
	UPROPERTY(BlueprintReadWrite)
	float LeanAmount;
	UPROPERTY(BlueprintReadWrite)
	FRotator CurrentRotation;
	UPROPERTY(BlueprintReadWrite)
	FRotator PreviousRotation;

protected:
	// Event Blueprint Update Animation 이벤트
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};