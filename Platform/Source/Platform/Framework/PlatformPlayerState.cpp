#include "PlatformPlayerState.h"
#include "Net/UnrealNetwork.h"

void APlatformPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		PlayerColorID = FMath::RandRange(0, 4);
		InitAppearance = true;
	}
}

void APlatformPlayerState::GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, PlayerColorID);
	DOREPLIFETIME(ThisClass, InitAppearance);
	DOREPLIFETIME(ThisClass, CheckPointTag);
}