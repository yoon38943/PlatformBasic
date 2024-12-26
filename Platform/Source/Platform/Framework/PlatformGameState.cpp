#include "PlatformGameState.h"

#include "PlatformPlayerController.h"
#include "PlatformGameMode.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"

void APlatformGameState::BeginPlay()
{
    Super::BeginPlay();

    GamePlayType = E_GamePlay::GameInit;

    // 서버는 카운트 다운 시작
    if (HasAuthority())
    {
        GamePlayType = E_GamePlay::ReadyCountdown;
        ServerCountDownProc();
    }
}

void APlatformGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
}



// void APlatformGameState::OnRep_RoundCountdown()
// {
//     PlayCountdownSound();
//     PlayReadyGoAnimation();
//
//     if (HasAuthority())
//     {
//         if (RoundCountDown == 0)
//         {
//             // 타이머 종료후 게임 시작
//             GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
//             StartRound();
//         }
//     }
// }
//
//
// void APlatformGameState::OnRep_PSWinnerRef()
// {
//     if (HasAuthority())
//     {
//         IsRoundEnded = true;
//     }
// }




void APlatformGameState::ServerCountDownProc()
{
    GamePlayType = E_GamePlay::ReadyCountdown;
    RoundCountDown = 10;    // Config 처리

    auto CountDownDelegate = [this]()
    {
        if (IsValid(this))
        {
            --RoundCountDown;
            NM_RoundCoundown(RoundCountDown);
            
            if (RoundCountDown == 0)
            {
                ServerStartRound(); // 게임 시작
            }
        }
    };
    
    GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle, CountDownDelegate, 1.0f, true);
}

void APlatformGameState::NM_RoundCoundown_Implementation(int32 Count)
{
    GamePlayType = E_GamePlay::ReadyCountdown;
    RoundCountDown = Count;

    // 카운트다운 사운드 출력
    if (Count > 0)
    {
        UGameplayStatics::PlaySound2D(GetWorld(), SB_Countdown);
    }
    else if (Count == 0)
    {
        UGameplayStatics::PlaySound2D(GetWorld(), SB_CountdownFinal);
    }

    // 2초 남았을 때
    if (Count == 2)
    {
        APlatformPlayerController* Controller = Cast<APlatformPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
        if (Controller)
        {
            Controller->ReadyGo();
        }
    }
}

void APlatformGameState::NM_IsRoundEnded_Implementation(APlayerState* WinnerPS)
{
   PSWinnerRef = WinnerPS;
    GamePlayType = E_GamePlay::GameResult;

    if (SB_RefereeWhistle)
    {
        UGameplayStatics::PlaySound2D(GetWorld(), SB_RefereeWhistle);
    }
                    
    APlatformPlayerController* Controller = Cast<APlatformPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
    if (Controller)
    {
        Controller->MatchOver();
    }
}

// 게임 시작 처리
void APlatformGameState::ServerStartRound()
{
    GamePlayType = E_GamePlay::GamePlaying;
    GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);

    APlatformGameMode* GM = Cast<APlatformGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    if (GM)
    {
        GM->EnableCharacter();
    }
}

void APlatformGameState::ServerPlayerWinner(APlayerState* WinnerPS)
{
    NM_IsRoundEnded(WinnerPS);
}
