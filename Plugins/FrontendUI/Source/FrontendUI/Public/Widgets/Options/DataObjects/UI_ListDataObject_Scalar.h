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

	static FCommonNumberFormattingOptions NoDecimal();
	static FCommonNumberFormattingOptions WithDecimal(const int32 NumFracDigit);

	float GetCurrentValue() const;
	void SetCurrentValueFromSlider(const float InNewValue);
	LIST_DATA_ACCESSOR(TRange<float>, DisplayValueRange);
	LIST_DATA_ACCESSOR(TRange<float>, OutputValueRange);
	LIST_DATA_ACCESSOR(float, SliderStepSize);
	LIST_DATA_ACCESSOR(ECommonNumericType, DisplayNumericType);
	LIST_DATA_ACCESSOR(FCommonNumberFormattingOptions, NumberFormattingOptions);

protected:

	/** UUI_ListDataObject_Base Parent */
	virtual bool CanResetBackToDefaultValue() const override;
	virtual bool TryResetBackToDefaultValue() override;
	virtual void OnEditDependencyDataModified(UUI_ListDataObject_Base* ModifiedDependencyData, const EOptionsListDataModifyReason ModifyReason = EOptionsListDataModifyReason::DirectlyModified) override;
	virtual bool CanSetToForcedStringValue(const FString& InForcedValue) const override;
	virtual void OnSetToForcedStringValue(const FString& InForcedValue) override;
	/** end UUI_ListDataObject_Base Parent */
	
private:

	float StringToFloat(const FString& InString) const;

	TRange<float> DisplayValueRange{ TRange<float>(0.f, 1.f) };
	TRange<float> OutputValueRange{ TRange<float>(0.f, 1.f) };
	float SliderStepSize{ 0.1f };

	ECommonNumericType DisplayNumericType{ ECommonNumericType::Number };
	FCommonNumberFormattingOptions NumberFormattingOptions;
};
