#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "PlatformGameState.generated.h"

// 게임의 진행상태를 나타내기 위한 Enum값
UENUM(BlueprintType)
enum class E_GamePlay : uint8
{
    GameInit,
    ReadyCountdown,
    GamePlaying,
    GameResult,
};

UCLASS()
class PLATFORM_API APlatformGameState : public AGameState
{
	GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, Category = Round)
    int32 RoundCountDown = 0;
    UPROPERTY(BlueprintReadWrite, Category = GameEnd)
    TObjectPtr<APlayerState> PSWinnerRef;
    UPROPERTY(BlueprintReadWrite, Category = GameEnd)
    E_GamePlay GamePlayType;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sound")
    TObjectPtr<USoundBase> SB_Countdown;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sound")
    TObjectPtr<USoundBase> SB_CountdownFinal;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sound")
    TObjectPtr<USoundBase> SB_RefereeWhistle;

public:
    FTimerHandle CountdownTimerHandle;

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    UFUNCTION(NetMulticast, Reliable)
    void NM_RoundCoundown(int32 Count);
    UFUNCTION(NetMulticast, Reliable)
    void NM_IsRoundEnded(APlayerState* WinnerPS);

    UFUNCTION(BlueprintCallable)
    void ServerPlayerWinner(APlayerState* WinnerPS);

public:
    void ServerStartRound();
    void ServerCountDownProc();
};