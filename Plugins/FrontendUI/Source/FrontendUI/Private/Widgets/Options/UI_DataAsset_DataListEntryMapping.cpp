// Eduard Ciofu All Rights Reserved


#include "Widgets/Options/UI_DataAsset_DataListEntryMapping.h"

#include "Widgets/Options/DataObjects/UI_ListDataObject_Base.h"

TSubclassOf<UUIWidget_ListEntry_Base> UUI_DataAsset_DataListEntryMapping::FindEntryWidgetClassByDataObject(const UUI_ListDataObject_Base* InDataObject) const
{
	check(InDataObject);

	for (UClass* DataObjectClass = InDataObject->GetClass(); DataObjectClass; DataObjectClass = DataObjectClass->GetSuperClass())
	{
		if (TSubclassOf<UUI_ListDataObject_Base> ConvertedDataObjectClass = TSubclassOf<UUI_ListDataObject_Base>(DataObjectClass))
		{
			if (DataObjectListEntryMap.Contains(ConvertedDataObjectClass))
			{
				return DataObjectListEntryMap.FindRef(ConvertedDataObjectClass);
			}
		}
	}

	return TSubclassOf<UUIWidget_ListEntry_Base>();
}
