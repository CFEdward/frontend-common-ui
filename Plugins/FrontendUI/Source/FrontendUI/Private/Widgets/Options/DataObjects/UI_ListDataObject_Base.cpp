// Eduard Ciofu All Rights Reserved


#include "Widgets/Options/DataObjects/UI_ListDataObject_Base.h"

#include "UISettings/UI_GameUserSettings.h"

void UUI_ListDataObject_Base::InitDataObject()
{
	OnDataObjectInitialized();
}

void UUI_ListDataObject_Base::AddEditCondition(const FOptionsDataEditConditionDescriptor& InEditCondition)
{
	EditConditionDescArray.Add(InEditCondition);
}

void UUI_ListDataObject_Base::AddEditDependencyData(UUI_ListDataObject_Base* InDependencyData)
{
	if (!InDependencyData->OnListDataModified.IsBoundToObject(this))
	{
		InDependencyData->OnListDataModified.AddUObject(this, &ThisClass::OnEditDependencyDataModified);
	}
}

bool UUI_ListDataObject_Base::IsDataCurrentlyEditable()
{
	bool bIsEditable = true;
	if (EditConditionDescArray.IsEmpty())
	{
		return bIsEditable;
	}

	FString CachedDisabledRichReason;
	for (const FOptionsDataEditConditionDescriptor& Condition : EditConditionDescArray)
	{
		if (!Condition.IsValid() || Condition.IsEditConditionMet()) continue;

		bIsEditable = false;
		CachedDisabledRichReason.Append(Condition.GetDisabledRichReason());
		SetDisabledRichText(FText::FromString(CachedDisabledRichReason));
		
		if (Condition.HasForcedStringValue())
		{
			const FString ForcedStringValue = Condition.GetDisabledForcedStringValue();

			// If the current value this Data Object has can be set to the Forced Value
			if (CanSetToForcedStringValue(ForcedStringValue))
			{
				OnSetToForcedStringValue(ForcedStringValue);
			}
		}
	}

	return bIsEditable;
}

void UUI_ListDataObject_Base::NotifyListDataModified(UUI_ListDataObject_Base* ModifiedData, const EOptionsListDataModifyReason ModifyReason)
{
	OnListDataModified.Broadcast(ModifiedData, ModifyReason);

	if (bShouldApplyChangeImmediately)
	{
		UUI_GameUserSettings::Get()->ApplySettings(true);
	}
}

void UUI_ListDataObject_Base::OnEditDependencyDataModified(UUI_ListDataObject_Base* ModifiedDependencyData, const EOptionsListDataModifyReason ModifyReason)
{
	OnDependencyDataModified.Broadcast(ModifiedDependencyData, ModifyReason);
}
