#include "PlatformGameState.h"

#include "Net/UnrealNetwork.h"

void APlatformGameState::BeginPlay()
{
	Super::BeginPlay();
}

void APlatformGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void APlatformGameState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, RoundCountDown);
	DOREPLIFETIME(ThisClass, IsRoundEnd);
	DOREPLIFETIME(ThisClass, PSWinnerRef);
}

void APlatformGameState::OnRep_RoundCountdown()
{
	// 카운트다운 사운드
	// 레디고 처리
	if (HasAuthority())
	{
		if (RoundCountDown == 0)
		{
			// 게임시작 처리
		}
	}
}

void APlatformGameState::OnRep_IsRoundEnded()
{
}

void APlatformGameState::OnRep_PSWinnerRef()
{
}

void APlatformGameState::CountdownProc()
{
	auto CountDownDelegate = [this]()
	{
		if (IsValid(this))
		{
			--RoundCountDown;
		}
	};

	GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle, CountDownDelegate, 1.f, false);
}
