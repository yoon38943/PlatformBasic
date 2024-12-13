#pragma once

#include "CoreMinimal.h"
#include "HCharBase.h"
#include "PlatformCharacter.generated.h"


UCLASS()
class PLATFORM_API APlatformCharacter : public AHCharBase
{
	GENERATED_BODY()
	
public:
	APlatformCharacter();
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaTime) override;

public:
	void UpdateSmoothingCamera(float DeltaTime);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};