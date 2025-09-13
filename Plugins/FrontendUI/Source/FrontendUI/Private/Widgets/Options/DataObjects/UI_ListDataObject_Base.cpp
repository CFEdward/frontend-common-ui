// Eduard Ciofu All Rights Reserved


#include "Widgets/Options/DataObjects/UI_ListDataObject_Base.h"

#include "UISettings/UI_GameUserSettings.h"

void UUI_ListDataObject_Base::InitDataObject()
{
	OnDataObjectInitialized();
}

void UUI_ListDataObject_Base::NotifyListDataModified(UUI_ListDataObject_Base* ModifiedData, const EOptionsListDataModifyReason ModifyReason)
{
	OnListDataModified.Broadcast(ModifiedData, ModifyReason);

	if (bShouldApplyChangeImmediately)
	{
		UUI_GameUserSettings::Get()->ApplySettings(true);
	}
}
