#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlatformPlayerController.generated.h"


UCLASS()
class PLATFORM_API APlatformPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ReadyGo();
	virtual void ReadyGo_Implementation() {};

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void MatchOver();
	virtual void MatchOver_Implementation() {};
};