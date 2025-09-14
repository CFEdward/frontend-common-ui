// Eduard Ciofu All Rights Reserved


#include "Widgets/Options/ListEntries/UIWidget_ListEntry_Base.h"

#include "CommonTextBlock.h"
#include "Components/ListView.h"
#include "Widgets/Options/DataObjects/UI_ListDataObject_Base.h"

void UUIWidget_ListEntry_Base::NativeOnListEntryWidgetHovered(const bool bWasHovered)
{
	BP_OnListEntryWidgetHovered(bWasHovered, IsListItemSelected());
}

void UUIWidget_ListEntry_Base::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	SetVisibility(ESlateVisibility::Visible);

	OnOwningListDataObjectSet(CastChecked<UUI_ListDataObject_Base>(ListItemObject));
}

void UUIWidget_ListEntry_Base::OnOwningListDataObjectSet(UUI_ListDataObject_Base* InOwningListDataObject)
{
	if (CommonText_SettingDisplayName)
	{
		CommonText_SettingDisplayName->SetText(InOwningListDataObject->GetDataDisplayName());
	}

	if (!InOwningListDataObject->OnListDataModified.IsBoundToObject(this))
	{
		InOwningListDataObject->OnListDataModified.AddUObject(this, &ThisClass::OnOwningListDataObjectModified);
	}
}

void UUIWidget_ListEntry_Base::OnOwningListDataObjectModified(UUI_ListDataObject_Base* OwningModifiedData, EOptionsListDataModifyReason ModifyReason)
{
}

void UUIWidget_ListEntry_Base::SelectThisEntryWidget() const
{
	CastChecked<UListView>(GetOwningListView())->SetSelectedItem(GetListItem());
}
