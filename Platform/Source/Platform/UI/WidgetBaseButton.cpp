#include "WidgetBaseButton.h"

#include "Components/Button.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/ButtonSlot.h"

void UWidgetBaseButton::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetBaseButtonStyle();
	SetBaseButtonSize();
	SetButtonTextFont();
}

void UWidgetBaseButton::NativeConstruct()
{
	Super::NativeConstruct();

	if (BTN_Base)
	{
		BTN_Base->OnClicked.AddDynamic(this, &ThisClass::OnClicked_Base);
	}
}

void UWidgetBaseButton::OnClicked_Base()
{
	BTN_BaseDelegate.Broadcast();
}

void UWidgetBaseButton::SetBaseButtonText(FString& Str)
{
	if (T_BtnText)
	{
		T_BtnText->SetText(FText::FromString(Str));
	}
}

void UWidgetBaseButton::SetBaseButtonStyle()
{
	if (BTN_Base == nullptr)
	{
		return;
	}

	// 설정할 버튼 스타일
	FButtonStyle NewButtonStyle;

	// 버튼의 기능별 슬레이트 브러시 생성
	if (T2D_Normal != nullptr)
	{
		FSlateBrush Brush;	// 노멀 상태
		Brush.DrawAs = ESlateBrushDrawType::Box;
		Brush.SetResourceObject(T2D_Normal);
		NewButtonStyle.SetNormal(Brush);
	}
	if (T2D_Hovered != nullptr)
	{
		FSlateBrush Brush;	// 포커싱 상태
		Brush.DrawAs = ESlateBrushDrawType::Box;
		Brush.SetResourceObject(T2D_Hovered);
		NewButtonStyle.SetHovered(Brush);
	}
	if (T2D_Pressed != nullptr)
	{
		FSlateBrush Brush;	// 눌림(클릭) 상태
		Brush.DrawAs = ESlateBrushDrawType::Box;
		Brush.SetResourceObject(T2D_Pressed);
		NewButtonStyle.SetPressed(Brush);
	}

	NewButtonStyle.SetDisabled(BTN_Base->GetStyle().Disabled);
	NewButtonStyle.SetNormalPadding(BTN_Base->GetStyle().NormalPadding);
	NewButtonStyle.SetPressedPadding(BTN_Base->GetStyle().PressedPadding);
	NewButtonStyle.SetHoveredSound(BTN_Base->GetStyle().HoveredSlateSound);
	NewButtonStyle.SetPressedSound(BTN_Base->GetStyle().PressedSlateSound);
	
	// 버튼 스타일을 새롭게 설정
	BTN_Base->SetStyle(NewButtonStyle);

	// 버튼 슬롯 설정
	UButtonSlot* GetSlot = Cast<UButtonSlot>(BTN_Base->GetContentSlot());
	if (GetSlot != nullptr)
	{
		GetSlot->SetHorizontalAlignment(Btn_HorizontalAlignment);
		GetSlot->SetPadding(Btn_Padding);
	}
}

void UWidgetBaseButton::SetBaseButtonSize()
{
	if (SB_Cover == nullptr)
	{
		return;
	}

	SB_Cover->SetWidthOverride(SB_CoverWidth);
	SB_Cover->SetHeightOverride(SB_CoverHeight);
}

void UWidgetBaseButton::SetButtonTextFont()
{
	if (T_BtnText == nullptr)
	{
		return;
	}

	// 폰트 객체 로드
	UObject* FontObject = LoadObject<UObject>(nullptr, TEXT("/Engine/EngineFonts/Roboto.Roboto"));
	if (!FontObject)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load font object!"));
		return;
	}

	// 슬레이트 폰트 정보 생성
	FSlateFontInfo FontInfo(FontObject, FontSize, FName("Bold"));
	// 폰트 적용
	T_BtnText->SetFont(FontInfo);
	T_BtnText->SetColorAndOpacity(FSlateColor(FontColor));
	T_BtnText->SetText(TextBtnCover);
}
