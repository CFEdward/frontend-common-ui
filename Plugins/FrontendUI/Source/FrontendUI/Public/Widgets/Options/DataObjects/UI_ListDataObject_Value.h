// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UI_ListDataObject_Base.h"
#include "UI_ListDataObject_Value.generated.h"

class FUI_OptionsDataInteractionHelper;

UCLASS(Abstract)
class FRONTENDUI_API UUI_ListDataObject_Value : public UUI_ListDataObject_Base
{
	GENERATED_BODY()

public:

	FORCEINLINE void SetDataDynamicGetter(const TSharedPtr<FUI_OptionsDataInteractionHelper>& InDynamicGetter);
	FORCEINLINE void SetDataDynamicSetter(const TSharedPtr<FUI_OptionsDataInteractionHelper>& InDynamicSetter);

	FORCEINLINE void SetDefaultValueFromString(const FString& InDefaultValue) { DefaultStringValue = InDefaultValue; }

	/** UUI_ListDataObject_Base Parent */
	virtual bool HasDefaultValue() const override { return DefaultStringValue.IsSet(); }
	/** end UUI_ListDataObject_Base Parent */
	
protected:

	FORCEINLINE FString GetDefaultValueAsString() const { return DefaultStringValue.GetValue(); }
	
	TSharedPtr<FUI_OptionsDataInteractionHelper> DataDynamicGetter;
	TSharedPtr<FUI_OptionsDataInteractionHelper> DataDynamicSetter;

private:

	TOptional<FString> DefaultStringValue;
};
