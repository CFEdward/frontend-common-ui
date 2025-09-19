// Eduard Ciofu All Rights Reserved


#include "Widgets/Options/DataObjects/UI_ListDataObject_Scalar.h"

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
