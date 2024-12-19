#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "PlatformGameState.generated.h"


UCLASS()
class PLATFORM_API APlatformGameState : public AGameState
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_RoundCountdown, Category = "Round")
	int32 RoundCountDown = 0;
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_IsRoundEnded, Category = "Round")
	bool IsRoundEnd = false;
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_PSWinnerRef)
	APlayerState* PSWinnerRef;

public:
	FTimerHandle CountdownTimerHandle;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	virtual void OnRep_RoundCountdown();
	UFUNCTION()
	virtual void OnRep_IsRoundEnded();
	UFUNCTION()
	virtual void OnRep_PSWinnerRef();

public:
	void CountdownProc();
};