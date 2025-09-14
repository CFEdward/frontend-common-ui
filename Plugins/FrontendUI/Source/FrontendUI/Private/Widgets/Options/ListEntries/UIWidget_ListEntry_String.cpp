// Eduard Ciofu All Rights Reserved


#include "Widgets/Options/ListEntries/UIWidget_ListEntry_String.h"

#include "Widgets/Components/UI_CommonButtonBase.h"
#include "Widgets/Components/UI_CommonRotator.h"
#include "Widgets/Options/DataObjects/UI_ListDataObject_String.h"

void UUIWidget_ListEntry_String::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CommonButton_PreviousOption->OnClicked().AddUObject(this, &ThisClass::OnPreviousOptionButtonClicked);
	CommonButton_NextOption->OnClicked().AddUObject(this, &ThisClass::OnNextOptionButtonClicked);

	CommonRotator_AvailableOptions->OnClicked().AddLambda([this]()
		{
			SelectThisEntryWidget();
		}
	);
}

void UUIWidget_ListEntry_String::OnOwningListDataObjectSet(UUI_ListDataObject_Base* InOwningListDataObject)
{
	Super::OnOwningListDataObjectSet(InOwningListDataObject);

	CachedOwningStringDataObject = CastChecked<UUI_ListDataObject_String>(InOwningListDataObject);

	CommonRotator_AvailableOptions->PopulateTextLabels(CachedOwningStringDataObject->GetAvailableOptionsTextArray());
	CommonRotator_AvailableOptions->SetSelectedOptionByText(CachedOwningStringDataObject->GetCurrentDisplayText());
}

void UUIWidget_ListEntry_String::OnOwningListDataObjectModified(UUI_ListDataObject_Base* OwningModifiedData, EOptionsListDataModifyReason ModifyReason)
{
	if (CachedOwningStringDataObject)
	{
		CommonRotator_AvailableOptions->SetSelectedOptionByText(CachedOwningStringDataObject->GetCurrentDisplayText());
	}
}

void UUIWidget_ListEntry_String::OnPreviousOptionButtonClicked() const
{
	if (CachedOwningStringDataObject)
	{
		CachedOwningStringDataObject->BackToPreviousOption();
	}

	SelectThisEntryWidget();
}

void UUIWidget_ListEntry_String::OnNextOptionButtonClicked() const
{
	if (CachedOwningStringDataObject)
	{
		CachedOwningStringDataObject->AdvanceToNextOption();
	}

	SelectThisEntryWidget();
}
