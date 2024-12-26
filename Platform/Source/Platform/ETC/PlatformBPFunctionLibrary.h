#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PlatformBPFunctionLibrary.generated.h"

UCLASS()
class PLATFORM_API UPlatformBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "HError Handling", meta = (WorldContext = "WorldContextObject"))	// WorldContextObject가 null 인것을 우아하게 넣어주기 위해 meta를 사용
	static bool IsActiveError(const UObject* WorldContextObject);
};
