// Eduard Ciofu All Rights Reserved


#include "Widgets/UIWidget_ConfirmScreen.h"

#include "CommonTextBlock.h"
#include "ICommonInputModule.h"
#include "Components/DynamicEntryBox.h"
#include "Widgets/Components/UI_CommonButtonBase.h"

UUI_ConfirmScreenInfoObject* UUI_ConfirmScreenInfoObject::CreateOKScreen(const FText& InScreenTitle, const FText& InScreenMessage)
{
	UUI_ConfirmScreenInfoObject* InfoObject = NewObject<UUI_ConfirmScreenInfoObject>();
	InfoObject->ScreenTitle = InScreenTitle;
	InfoObject->ScreenMessage = InScreenMessage;

	FConfirmScreenButtonInfo OKButtonInfo;
	OKButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Closed;
	OKButtonInfo.ButtonTextToDisplay = FText::FromString("OK");
	InfoObject->AvailableScreenButtons.Add(OKButtonInfo);

	return InfoObject;
}

UUI_ConfirmScreenInfoObject* UUI_ConfirmScreenInfoObject::CreateYesNoScreen(const FText& InScreenTitle, const FText& InScreenMessage)
{
	UUI_ConfirmScreenInfoObject* InfoObject = NewObject<UUI_ConfirmScreenInfoObject>();
	InfoObject->ScreenTitle = InScreenTitle;
	InfoObject->ScreenMessage = InScreenMessage;

	FConfirmScreenButtonInfo YesButtonInfo;
	YesButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Confirmed;
	YesButtonInfo.ButtonTextToDisplay = FText::FromString("Yes");
	InfoObject->AvailableScreenButtons.Add(YesButtonInfo);

	FConfirmScreenButtonInfo NoButtonInfo;
	NoButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Cancelled;
	NoButtonInfo.ButtonTextToDisplay = FText::FromString("No");
	InfoObject->AvailableScreenButtons.Add(NoButtonInfo);

	return InfoObject;
}

UUI_ConfirmScreenInfoObject* UUI_ConfirmScreenInfoObject::CreateOKCancelScreen(const FText& InScreenTitle, const FText& InScreenMessage)
{
	UUI_ConfirmScreenInfoObject* InfoObject = NewObject<UUI_ConfirmScreenInfoObject>();
	InfoObject->ScreenTitle = InScreenTitle;
	InfoObject->ScreenMessage = InScreenMessage;

	FConfirmScreenButtonInfo OKButtonInfo;
	OKButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Confirmed;
	OKButtonInfo.ButtonTextToDisplay = FText::FromString("OK");
	InfoObject->AvailableScreenButtons.Add(OKButtonInfo);

	FConfirmScreenButtonInfo CancelButtonInfo;
	CancelButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Cancelled;
	CancelButtonInfo.ButtonTextToDisplay = FText::FromString("Cancel");
	InfoObject->AvailableScreenButtons.Add(CancelButtonInfo);

	return InfoObject;
}

void UUIWidget_ConfirmScreen::InitConfirmScreen(UUI_ConfirmScreenInfoObject* InScreenInfoObject, TFunction<void(EConfirmScreenButtonType)> ClickedButtonCallback)
{
	check(InScreenInfoObject && CommonTextBlock_Title && CommonTextBlock_Message && DynamicEntryBox_Buttons);

	CommonTextBlock_Title->SetText(InScreenInfoObject->ScreenTitle);
	CommonTextBlock_Message->SetText(InScreenInfoObject->ScreenMessage);

	// Checking if the entry box has old buttons created previously
	if (DynamicEntryBox_Buttons->GetNumEntries() != 0)
	{
		// Clearing the old buttons the entry box has.
		// The widget type for the entry box is specified in the child widget blueprint
		DynamicEntryBox_Buttons->Reset<UUI_CommonButtonBase>([](const UUI_CommonButtonBase& ExistingButton)
			{
				ExistingButton.OnClicked().Clear();
			}
		);
	}

	check(!InScreenInfoObject->AvailableScreenButtons.IsEmpty());

	for (const FConfirmScreenButtonInfo& AvailableButtonInfo : InScreenInfoObject->AvailableScreenButtons)
	{
		FDataTableRowHandle InputActionRowHandle;
		
		switch (AvailableButtonInfo.ConfirmScreenButtonType)
		{
		case EConfirmScreenButtonType::Cancelled:
			InputActionRowHandle = ICommonInputModule::GetSettings().GetDefaultBackAction();
			break;

		case EConfirmScreenButtonType::Closed:
			InputActionRowHandle = ICommonInputModule::GetSettings().GetDefaultBackAction();
			break;
			
		default:
			break;
		}
		
		UUI_CommonButtonBase* AddedButton = DynamicEntryBox_Buttons->CreateEntry<UUI_CommonButtonBase>();
		AddedButton->SetButtonText(AvailableButtonInfo.ButtonTextToDisplay);
		AddedButton->SetTriggeringInputAction(InputActionRowHandle);
		AddedButton->OnClicked().AddLambda([this, ClickedButtonCallback, AvailableButtonInfo]()
			{
				ClickedButtonCallback(AvailableButtonInfo.ConfirmScreenButtonType);
				DeactivateWidget();
			}
		);
	}
}

UWidget* UUIWidget_ConfirmScreen::NativeGetDesiredFocusTarget() const
{
	// Set focus on the last button so Gamepad has an option to start with.
	if (DynamicEntryBox_Buttons->GetNumEntries() != 0)
	{
		// Set focus on the last button. So if there are two buttons, ex.
		// one is Yes, one is No, our gamepad will focus on the No Button
		DynamicEntryBox_Buttons->GetAllEntries().Last()->SetFocus();
	}
	
	return Super::NativeGetDesiredFocusTarget();
}
