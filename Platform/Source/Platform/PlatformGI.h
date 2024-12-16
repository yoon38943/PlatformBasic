#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PlatformGI.generated.h"

UCLASS()
class PLATFORM_API UPlatformGI : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "HError Handling")
	FString HNetworkError;	// 넷 드라이버의 통신에러
	UPROPERTY(BlueprintReadWrite, Category = "HError Handling")
	FString HTravelError;	// 서브 트러블 에러
	
};
