#include "PlatformBPFunctionLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "Platform/PlatformGI.h"

// 게임 인스턴스에 캐싱된 네트워크 오류가 있는지 체크 / 보통 호스트와 연결이 끊어졌을 때
bool UPlatformBPFunctionLibrary::IsActiveError(const UObject* WorldContextObject)
{
	UPlatformGI* GI = Cast<UPlatformGI>(UGameplayStatics::GetGameInstance(WorldContextObject));
	if (GI != nullptr)
	{
		if (GI->HNetworkError.IsEmpty())
		{
			if (GI->HTravelError.IsEmpty())
			{
				return false;	// 에러 없음
			}
			else
			{
				return true;	// 서버 트레블 에러
			}
		}
		else
		{
			return true;	// 네트워크 에러
		}
	}

	check(nullptr);	// 위에서 반드시 리턴한다
	return true;
}
