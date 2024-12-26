#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetBaseButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClickedDelegate);

UCLASS()
class PLATFORM_API UWidgetBaseButton : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<class UTexture2D> T2D_Normal;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UTexture2D> T2D_Hovered;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UTexture2D> T2D_Pressed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float SB_CoverWidth;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float SB_CoverHeight;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLinearColor FontColor;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 FontSize;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText TextBtnCover;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<EHorizontalAlignment> Btn_HorizontalAlignment;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FMargin Btn_Padding;
	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class USizeBox> SB_Cover;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> T_BtnText;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> BTN_Base;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnButtonClickedDelegate BTN_BaseDelegate;

public:
	UFUNCTION(BlueprintCallable, Category = "Events")
	void OnClicked_Base();

	UFUNCTION(BlueprintCallable)
	void SetBaseButtonText(FString& Str);

protected:
	void SetBaseButtonStyle();
	void SetBaseButtonSize();
	void SetButtonTextFont();
};
