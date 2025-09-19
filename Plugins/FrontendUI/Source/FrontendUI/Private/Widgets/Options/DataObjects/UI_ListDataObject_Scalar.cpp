// Eduard Ciofu All Rights Reserved


#include "Widgets/Options/DataObjects/UI_ListDataObject_Scalar.h"

#include "Widgets/Options/UI_OptionsDataInteractionHelper.h"

FCommonNumberFormattingOptions UUI_ListDataObject_Scalar::NoDecimal()
{
	FCommonNumberFormattingOptions Options;
	Options.MaximumFractionalDigits = 0;

	return Options;
}

FCommonNumberFormattingOptions UUI_ListDataObject_Scalar::WithDecimal(const int32 NumFracDigit)
{
	FCommonNumberFormattingOptions Options;
	Options.MaximumFractionalDigits = NumFracDigit;

	return Options;
}

float UUI_ListDataObject_Scalar::GetCurrentValue() const
{
	if (DataDynamicGetter)
	{
		return FMath::GetMappedRangeValueClamped(
			OutputValueRange,
			DisplayValueRange,
			StringToFloat(DataDynamicGetter->GetValueAsString())
		);
	}

	return 0.f;
}

float UUI_ListDataObject_Scalar::StringToFloat(const FString& InString) const
{
	float OutConvertedValue = 0.f;
	LexFromString(OutConvertedValue, *InString);

	return OutConvertedValue;
}
