#pragma once

#include "CoreMinimal.h"
#include "HCharBase.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "PlatformCharacter.generated.h"


UCLASS()
class PLATFORM_API APlatformCharacter : public AHCharBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* IA_Pause;
	
	APlatformCharacter();
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaTime) override;

	void Pause(const FInputActionValue& Value);


public:
	void UpdateSmoothingCamera(float DeltaTime);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	IOnlineSessionPtr OnlineSessionInterface;	// (스팀) 온라인 서브시스템 인터페이스

protected:
	// 클라가 세션을 생성하는 명령
	UFUNCTION(BlueprintCallable)
	void CreateGameSession();
	void FindGameSession();

	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

private:
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
};
