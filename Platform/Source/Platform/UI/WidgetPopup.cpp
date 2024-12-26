#include "WidgetPopup.h"
#include "WidgetBaseButton.h"
#include "Components/TextBlock.h"


void UWidgetPopup::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (T_PopupText)
	{
		T_PopupText->SetText(Text_Popup);
	}

	if (WBP_ButtonOK && WBP_ButtonOK->T_BtnText)
	{
		WBP_ButtonOK->T_BtnText->SetText(Text_OKBtn);
	}

	if (WBP_ButtonCancel)
	{
		if (IsShowCancelBtn)
		{
			WBP_ButtonCancel->SetVisibility(ESlateVisibility::Visible);
			if (WBP_ButtonCancel->T_BtnText)
			{
				WBP_ButtonCancel->T_BtnText->SetText(Text_CancelBtn);
			}
		}
		else
		{
			WBP_ButtonCancel->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UWidgetPopup::NativeConstruct()
{
	Super::NativeConstruct();

	WBP_ButtonOK->BTN_BaseDelegate.AddDynamic(this, &ThisClass::OnClickedOKBtn);
	WBP_ButtonCancel->BTN_BaseDelegate.AddDynamic(this, &ThisClass::OnClickedCancelBtn);
}

void UWidgetPopup::OnClickedOKBtn()
{
	RemoveFromParent();
	ButtonOKDelegate.Broadcast();
}

void UWidgetPopup::OnClickedCancelBtn()
{
	RemoveFromParent();
	ButtonCancelDelegate.Broadcast();
}