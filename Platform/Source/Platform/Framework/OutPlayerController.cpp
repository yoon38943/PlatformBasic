#include "OutPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


AOutPlayerController::AOutPlayerController()
{
	SetShowMouseCursor(true);
}

void AOutPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController() && MainMenuClass != nullptr)
	{
		MainMenu = CreateWidget<UUserWidget>(this, MainMenuClass);
		if (MainMenu)
		{
			MainMenu->AddToViewport(0);

			UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this, MainMenu, EMouseLockMode::DoNotLock);

			// TODO: 네트워크 에러 판별 코드 추가
		}
	}
}
