// Eduard Ciofu All Rights Reserved


#include "Widgets/Options/DataObjects/UI_ListDataObject_Collection.h"

TArray<UUI_ListDataObject_Base*> UUI_ListDataObject_Collection::GetAllChildListData() const
{
	return ChildListDataArray;
}

bool UUI_ListDataObject_Collection::HasAnyChildListData() const
{
	return !ChildListDataArray.IsEmpty();
}

void UUI_ListDataObject_Collection::AddChildListData(UUI_ListDataObject_Base* InChildListData)
{
	// Notify the child list data to init itself
	InChildListData->InitDataObject();

	// Set the child list data's parent to this
	InChildListData->SetParentData(this);
	
	ChildListDataArray.Add(InChildListData);
}
