// Eduard Ciofu All Rights Reserved


#include "Widgets/UIWidget_ConfirmScreen.h"

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
