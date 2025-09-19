// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonNumericTextBlock.h"
#include "UI_ListDataObject_Value.h"
#include "UI_ListDataObject_Scalar.generated.h"

UCLASS()
class FRONTENDUI_API UUI_ListDataObject_Scalar : public UUI_ListDataObject_Value
{
	GENERATED_BODY()

public:

	LIST_DATA_ACCESSOR(TRange<float>, DisplayValueRange);
	LIST_DATA_ACCESSOR(TRange<float>, OutputValueRange);
	LIST_DATA_ACCESSOR(float, SliderStepSize);
	LIST_DATA_ACCESSOR(ECommonNumericType, DisplayNumericType);
	LIST_DATA_ACCESSOR(FCommonNumberFormattingOptions, NumberFormattingOptions);

	static FCommonNumberFormattingOptions NoDecimal();
	static FCommonNumberFormattingOptions WithDecimal(const int32 NumFracDigit);
	
private:

	TRange<float> DisplayValueRange{ TRange<float>(0.f, 1.f) };
	TRange<float> OutputValueRange{ TRange<float>(0.f, 1.f) };
	float SliderStepSize{ 0.1f };

	ECommonNumericType DisplayNumericType{ ECommonNumericType::Number };
	FCommonNumberFormattingOptions NumberFormattingOptions;
};
