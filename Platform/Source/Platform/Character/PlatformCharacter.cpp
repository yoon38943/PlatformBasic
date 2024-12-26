#include "PlatformCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../ETC/HDebugMacros.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"


APlatformCharacter::APlatformCharacter()
{
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.25f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// ------------------------------------------------------------------------------------

	CreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionComplete);
	FindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &ThisClass::OnFindSessionComplete);
	JoinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnJoinSessionComplete);
	
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		OnlineSessionInterface = OnlineSubsystem->GetSessionInterface();
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue,
				FString::Printf(TEXT("Found subsystem %s"), *OnlineSubsystem->GetSubsystemName().ToString()));
		}
	}
}

void APlatformCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void APlatformCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateSmoothingCamera(DeltaTime);
}

void APlatformCharacter::Pause(const FInputActionValue& Value)
{
}

void APlatformCharacter::UpdateSmoothingCamera(float DeltaTime)
{
	FVector VStart = GetActorLocation();
	TArray<AActor*> ActorsToIgnore;

	FHitResult HitResult;
	bool IsHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), VStart, VStart + FVector(0.f, 0.f, 250.f),
			UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Camera), false, ActorsToIgnore,
			EDrawDebugTrace::None, HitResult, true);

	float DesiredTargetArmLenght = 300.f;
	if (IsHit == false)
	{
		DesiredTargetArmLenght = 600.f;
		if (GetMovementComponent()->IsFalling())
		{
			DesiredTargetArmLenght = 1000.f;
		}
	}

	float CurrentArmLength = FMath::FInterpTo(GetCameraBoom()->TargetArmLength, DesiredTargetArmLenght , DeltaTime, 1.f);
	GetCameraBoom()->TargetArmLength = CurrentArmLength;
}

void APlatformCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlatformCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (EndPlayReason == EEndPlayReason::Destroyed)
	{
	}
}

void APlatformCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 나중에 추가되는 입력만 처리
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
//h		EnhancedInputComponent->BindAction(CommandAction, ETriggerEvent::Triggered, this, &APlatformCharacter::RPCCommand);
	}
}

// (스팀) 세션 생성 완료시 호출
void APlatformCharacter::CreateGameSession()
{
	if (!OnlineSessionInterface.IsValid())
	{
		return;
	}

	// 기존에 세션이 존재 하는지 확인
	FNamedOnlineSession* ExistingSession = OnlineSessionInterface->GetNamedSession(NAME_GameSession);
	if (ExistingSession)
	{
		OnlineSessionInterface->DestroySession(NAME_GameSession);
	}

	OnlineSessionInterface->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);

	TSharedPtr<FOnlineSessionSettings> SessionSettings = MakeShareable(new FOnlineSessionSettings());
	SessionSettings->bIsLANMatch = false;	// LAN 컨넥션
	SessionSettings->NumPublicConnections = 4;	// 세션 참여 인원
	SessionSettings->bAllowJoinInProgress = true;	// 세션 실행중에 다른 유저가 조인할 수 있는지
	SessionSettings->bAllowJoinViaPresence = true;	// 내 근처에 있는 유저 우선
	SessionSettings->bShouldAdvertise = true;	// 세션 광고여부
	SessionSettings->bUsesPresence = true;	// 내가 있는 지역에서 진행중인 세션 검색
	SessionSettings->bUseLobbiesIfAvailable = true;	// 대상 플랫폼이 로비 API를 지원할 때 그 로비 API를 사용할거냐
	SessionSettings->Set(FName("MatchType"), FString("FreeForAll"), EOnlineDataAdvertisementType::ViaPingOnly);

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	OnlineSessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *SessionSettings);
}

void APlatformCharacter::FindGameSession()
{
	if (!OnlineSessionInterface.IsValid())
	{
		return;
	}

	OnlineSessionInterface->AddOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteDelegate);

	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->MaxSearchResults = 10000;
	SessionSearch->bIsLanQuery = false;
	SessionSearch->QuerySettings.Set(TEXT("PRESENCESEARCH"), true, EOnlineComparisonOp::Equals);

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	OnlineSessionInterface->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(), SessionSearch.ToSharedRef());
}

void APlatformCharacter::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue,
				FString::Printf(TEXT("Create Session!! : %s"), *SessionName.ToString()));
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red,
				FString::Printf(TEXT("Failed to Create Session!!")));
		}
	}
}

void APlatformCharacter::OnFindSessionComplete(bool bWasSuccessful)
{
	if (!OnlineSessionInterface.IsValid())
	{
		return;
	}
	
	for (auto Result : SessionSearch->SearchResults)
	{
		FString Id = Result.GetSessionIdStr();
		FString User = Result.Session.OwningUserName;
		FString MatchType;
		Result.Session.SessionSettings.Get(FName("MatchType"), MatchType);
		
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue,
				FString::Printf(TEXT("Find Session [ID : %s / User : %s]"), *Id, *User));

			OnlineSessionInterface->AddOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegate);
			// 테스트 삼아 바로 진입
			const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
			OnlineSessionInterface->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, Result);
		}
	}
}

void APlatformCharacter::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (!OnlineSessionInterface.IsValid())
	{
		return;
	}

	FString Address;
	if (OnlineSessionInterface->GetResolvedConnectString(NAME_GameSession, Address))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow,
			FString::Printf(TEXT("Connect String [%s]"), *Address));
		APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
		if (PlayerController)
		{
			PlayerController->ClientTravel(Address, TRAVEL_Absolute);
		}
	}
}