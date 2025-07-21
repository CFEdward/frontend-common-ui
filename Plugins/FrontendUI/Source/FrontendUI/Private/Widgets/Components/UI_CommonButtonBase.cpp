// Eduard Ciofu All Rights Reserved


#include "Widgets/Components/UI_CommonButtonBase.h"

#include "CommonTextBlock.h"
#include "Subsystems/UI_Subsystem.h"

void UUI_CommonButtonBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetButtonText(ButtonDisplayText);
}

void UUI_CommonButtonBase::NativeOnCurrentTextStyleChanged()
{
	Super::NativeOnCurrentTextStyleChanged();

	if (CommonTextBlock_ButtonText && GetCurrentTextStyleClass())
	{
		CommonTextBlock_ButtonText->SetStyle(GetCurrentTextStyleClass());
	}
}

void UUI_CommonButtonBase::NativeOnHovered()
{
	Super::NativeOnHovered();

	if (!ButtonDescriptionText.IsEmpty())
	{
		UUI_Subsystem::Get(this)->OnButtonDescriptionTextUpdated.Broadcast(this, ButtonDescriptionText);
	}
}

void UUI_CommonButtonBase::NativeOnUnhovered()
{
	Super::NativeOnUnhovered();

	UUI_Subsystem::Get(this)->OnButtonDescriptionTextUpdated.Broadcast(this, FText::GetEmpty());
}

void UUI_CommonButtonBase::SetButtonText(const FText InText) const
{
	if (CommonTextBlock_ButtonText && !InText.IsEmpty())
	{
		CommonTextBlock_ButtonText->SetText(bUseUpperCaseForButtonText ? InText.ToUpper() : InText);
	}
}
