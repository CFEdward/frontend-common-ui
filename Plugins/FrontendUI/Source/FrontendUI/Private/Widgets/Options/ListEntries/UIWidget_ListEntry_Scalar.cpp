// Eduard Ciofu All Rights Reserved


#include "Widgets/Options/ListEntries/UIWidget_ListEntry_Scalar.h"

#include "AnalogSlider.h"
#include "Widgets/Options/DataObjects/UI_ListDataObject_Scalar.h"

void UUIWidget_ListEntry_Scalar::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
}

void UUIWidget_ListEntry_Scalar::OnOwningListDataObjectSet(UUI_ListDataObject_Base* InOwningListDataObject)
{
	Super::OnOwningListDataObjectSet(InOwningListDataObject);

	CachedOwningScalarDataObject = CastChecked<UUI_ListDataObject_Scalar>(InOwningListDataObject);
	
	CommonNumeric_SettingValue->SetNumericType(CachedOwningScalarDataObject->GetDisplayNumericType());
	CommonNumeric_SettingValue->FormattingSpecification = CachedOwningScalarDataObject->GetNumberFormattingOptions();
	CommonNumeric_SettingValue->SetCurrentValue(CachedOwningScalarDataObject->GetCurrentValue());

	AnalogSlider_Setting->SetMinValue(CachedOwningScalarDataObject->GetDisplayValueRange().GetLowerBoundValue());
	AnalogSlider_Setting->SetMaxValue(CachedOwningScalarDataObject->GetDisplayValueRange().GetUpperBoundValue());
	AnalogSlider_Setting->SetStepSize(CachedOwningScalarDataObject->GetSliderStepSize());
	AnalogSlider_Setting->SetValue(CachedOwningScalarDataObject->GetCurrentValue());
}

void UUIWidget_ListEntry_Scalar::OnOwningListDataObjectModified(UUI_ListDataObject_Base* OwningModifiedData, EOptionsListDataModifyReason ModifyReason)
{
	if (IsValid(CachedOwningScalarDataObject))
	{
		CommonNumeric_SettingValue->SetCurrentValue(CachedOwningScalarDataObject->GetCurrentValue());
		AnalogSlider_Setting->SetValue(CachedOwningScalarDataObject->GetCurrentValue());
	}
}
