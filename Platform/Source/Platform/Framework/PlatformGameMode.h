#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PlatformGameMode.generated.h"


UCLASS()
class PLATFORM_API APlatformGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	TArray<class APlayerController*> AllPlayerController;

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	virtual void SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC) override;
};