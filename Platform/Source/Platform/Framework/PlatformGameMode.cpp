#include "PlatformGameMode.h"

void APlatformGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (NewPlayer)
	{
		AllPlayerController.Add(NewPlayer);
	}
}

void APlatformGameMode::Logout(AController* Exiting)
{
	if (APlayerController* PC = Cast<APlayerController>(Exiting))
	{
		AllPlayerController.Remove(PC);
	}
	
	Super::Logout(Exiting);
}

void APlatformGameMode::SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC)
{
	Super::SwapPlayerControllers(OldPC, NewPC);

	if (NewPC)
	{
		AllPlayerController.Add(NewPC);
	}
}
