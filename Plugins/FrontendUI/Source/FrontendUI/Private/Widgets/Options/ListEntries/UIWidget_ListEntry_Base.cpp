// Eduard Ciofu All Rights Reserved


#include "Widgets/Options/ListEntries/UIWidget_ListEntry_Base.h"

#include "CommonTextBlock.h"
#include "Widgets/Options/DataObjects/UI_ListDataObject_Base.h"

void UUIWidget_ListEntry_Base::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	OnOwningListDataObjectSet(CastChecked<UUI_ListDataObject_Base>(ListItemObject));
}

void UUIWidget_ListEntry_Base::OnOwningListDataObjectSet(UUI_ListDataObject_Base* InOwningListDataObject)
{
	if (CommonText_SettingDisplayName)
	{
		CommonText_SettingDisplayName->SetText(InOwningListDataObject->GetDataDisplayName());
	}
}
