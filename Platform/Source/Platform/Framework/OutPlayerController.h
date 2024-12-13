#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OutPlayerController.generated.h"


UCLASS()
class PLATFORM_API AOutPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> MainMenuClass;

	UPROPERTY()
	class UUserWidget* MainMenu;
	
protected:
	virtual void BeginPlay() override;
};