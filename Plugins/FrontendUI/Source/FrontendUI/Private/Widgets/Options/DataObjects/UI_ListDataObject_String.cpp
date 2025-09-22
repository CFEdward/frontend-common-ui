// Eduard Ciofu All Rights Reserved


#include "Widgets/Options/DataObjects/UI_ListDataObject_String.h"

#include "UI_DebugHelper.h"
#include "Widgets/Options/UI_OptionsDataInteractionHelper.h"

void UUI_ListDataObject_String::OnDataObjectInitialized()
{
	if (!AvailableOptionsStringArray.IsEmpty())
	{
		CurrentStringValue = AvailableOptionsStringArray[0];
	}

	if (HasDefaultValue())
	{
		CurrentStringValue = GetDefaultValueAsString();
	}
	
	if (DataDynamicGetter)
	{
		if (!DataDynamicGetter->GetValueAsString().IsEmpty())
		{
			CurrentStringValue = DataDynamicGetter->GetValueAsString();
		}
	}

	if (!TrySetDisplayTextFromStringValue(CurrentStringValue))
	{
		CurrentDisplayText = FText::FromString(TEXT("Invalid Option"));
	}
}

void UUI_ListDataObject_String::AddDynamicOption(const FString& InStringValue, const FText& InDisplayText)
{
	AvailableOptionsStringArray.Add(InStringValue);
	AvailableOptionsTextArray.Add(InDisplayText);
}

void UUI_ListDataObject_String::AdvanceToNextOption()
{
	if (AvailableOptionsStringArray.IsEmpty() || AvailableOptionsTextArray.IsEmpty()) return;

	const int32 CurrentDisplayIndex = AvailableOptionsStringArray.IndexOfByKey(CurrentStringValue);
	const int32 NextIndexToDisplay = CurrentDisplayIndex + 1;

	const bool bIsNextIndexValid = AvailableOptionsStringArray.IsValidIndex(NextIndexToDisplay);
	CurrentStringValue = bIsNextIndexValid ? AvailableOptionsStringArray[NextIndexToDisplay] : AvailableOptionsStringArray[0];

	TrySetDisplayTextFromStringValue(CurrentStringValue);
	if (DataDynamicSetter)
	{
		DataDynamicSetter->SetValueFromString(CurrentStringValue);
		Debug::Print(TEXT("DataDynamicSetter is used. The latest value from Getter: ") + DataDynamicGetter->GetValueAsString());
		NotifyListDataModified(this);
	}
}

void UUI_ListDataObject_String::BackToPreviousOption()
{
	if (AvailableOptionsStringArray.IsEmpty() || AvailableOptionsTextArray.IsEmpty()) return;

	const int32 CurrentDisplayIndex = AvailableOptionsStringArray.IndexOfByKey(CurrentStringValue);
	const int32 PreviousIndexToDisplay = CurrentDisplayIndex - 1;

	const bool bIsPreviousIndexValid = AvailableOptionsStringArray.IsValidIndex(PreviousIndexToDisplay);
	CurrentStringValue = bIsPreviousIndexValid ? AvailableOptionsStringArray[PreviousIndexToDisplay] : AvailableOptionsStringArray.Last();

	TrySetDisplayTextFromStringValue(CurrentStringValue);
	if (DataDynamicSetter)
	{
		DataDynamicSetter->SetValueFromString(CurrentStringValue);
		Debug::Print(TEXT("DataDynamicSetter is used. The latest value from Getter: ") + DataDynamicGetter->GetValueAsString());
		NotifyListDataModified(this);
	}
}

void UUI_ListDataObject_String::OnRotatorInitiatedValueChange(const FText& InNewSelectedText)
{
	const int32 FoundIndex = AvailableOptionsTextArray.IndexOfByPredicate([InNewSelectedText](const FText& AvailableText)->bool
		{
			return AvailableText.EqualTo(InNewSelectedText);
		}
	);

	if (FoundIndex != INDEX_NONE && AvailableOptionsStringArray.IsValidIndex(FoundIndex))
	{
		CurrentDisplayText = InNewSelectedText;
		CurrentStringValue = AvailableOptionsStringArray[FoundIndex];
		
		if (DataDynamicSetter)
		{
			DataDynamicSetter->SetValueFromString(CurrentStringValue);

			NotifyListDataModified(this);
		}
	}
}

bool UUI_ListDataObject_String::CanResetBackToDefaultValue() const
{
	return HasDefaultValue() && CurrentStringValue != GetDefaultValueAsString();
}

bool UUI_ListDataObject_String::TryResetBackToDefaultValue()
{
	if (CanResetBackToDefaultValue())
	{
		CurrentStringValue = GetDefaultValueAsString();
		TrySetDisplayTextFromStringValue(CurrentStringValue);

		if (DataDynamicSetter)
		{
			DataDynamicSetter->SetValueFromString(CurrentStringValue);
			NotifyListDataModified(this, EOptionsListDataModifyReason::ResetToDefault);

			return true;
		}
	}

	return false;
}

bool UUI_ListDataObject_String::CanSetToForcedStringValue(const FString& InForcedValue) const
{
	return CurrentStringValue != InForcedValue;
}

void UUI_ListDataObject_String::OnSetToForcedStringValue(const FString& InForcedValue)
{
	CurrentStringValue = InForcedValue;
	TrySetDisplayTextFromStringValue(CurrentStringValue);

	if (DataDynamicSetter)
	{
		DataDynamicSetter->SetValueFromString(CurrentStringValue);

		NotifyListDataModified(this, EOptionsListDataModifyReason::DependencyModified);
	}
}

bool UUI_ListDataObject_String::TrySetDisplayTextFromStringValue(const FString& InStringValue)
{
	const int32 CurrentFoundIndex = AvailableOptionsStringArray.IndexOfByKey(InStringValue);
	if (AvailableOptionsTextArray.IsValidIndex(CurrentFoundIndex))
	{
		CurrentDisplayText = AvailableOptionsTextArray[CurrentFoundIndex];

		return true;
	}

	return false;
}

/************ UUI_ListDataObject_StringBool ************/

void UUI_ListDataObject_StringBool::OnDataObjectInitialized()
{
	TryInitBoolValues();
	
	Super::OnDataObjectInitialized();
}

void UUI_ListDataObject_StringBool::TryInitBoolValues()
{
	if (!AvailableOptionsStringArray.Contains(TrueString))
	{
		AddDynamicOption(TrueString, FText::FromString(TEXT("ON")));
	}
	if (!AvailableOptionsStringArray.Contains(FalseString))
	{
		AddDynamicOption(FalseString, FText::FromString(TEXT("OFF")));
	}
}

void UUI_ListDataObject_StringBool::OverrideTrueDisplayText(const FText& InNewTrueDisplayText)
{
	if (!AvailableOptionsStringArray.Contains(TrueString))
	{
		AddDynamicOption(TrueString, InNewTrueDisplayText);
	}
}

void UUI_ListDataObject_StringBool::OverrideFalseDisplayText(const FText& InNewFalseDisplayText)
{
	if (!AvailableOptionsStringArray.Contains(FalseString))
	{
		AddDynamicOption(FalseString, InNewFalseDisplayText);
	}
}

void UUI_ListDataObject_StringBool::SetTrueAsDefaultValue()
{
	SetDefaultValueFromString(TrueString);
}

void UUI_ListDataObject_StringBool::SetFalseAsDefaultValue()
{
	SetDefaultValueFromString(FalseString);
}

/************ UUI_ListDataObject_StringInteger ************/

void UUI_ListDataObject_StringInteger::AddIntegerOption(const int32 InIntegerValue, const FText& InDisplayText)
{
	AddDynamicOption(LexToString(InIntegerValue), InDisplayText);
}

void UUI_ListDataObject_StringInteger::OnEditDependencyDataModified(UUI_ListDataObject_Base* ModifiedDependencyData, const EOptionsListDataModifyReason ModifyReason)
{
	if (DataDynamicGetter)
	{
		CurrentStringValue = DataDynamicGetter->GetValueAsString();

		if (!TrySetDisplayTextFromStringValue(CurrentStringValue))
		{
			CurrentDisplayText = FText::FromString(TEXT("Custom"));
		}

		NotifyListDataModified(this, EOptionsListDataModifyReason::DependencyModified);
	}

	Super::OnEditDependencyDataModified(ModifiedDependencyData, ModifyReason);
}

void UUI_ListDataObject_StringInteger::OnDataObjectInitialized()
{
	Super::OnDataObjectInitialized();

	if (!TrySetDisplayTextFromStringValue(CurrentStringValue))
	{
		CurrentDisplayText = FText::FromString(TEXT("Custom"));
	}
}
