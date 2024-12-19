#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlatformPlayerState.generated.h"


UCLASS()
class PLATFORM_API APlatformPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, Replicated, Category = Appearance)
	int32 PlayerColorID = 0;
	UPROPERTY(BlueprintReadWrite, Replicated, Category = Appearance)
	bool InitAppearance = false;
	UPROPERTY(BlueprintReadWrite, Replicated, Category = CheckPoint)
	FName CheckPointTag;

protected:
	virtual void BeginPlay() override;
};