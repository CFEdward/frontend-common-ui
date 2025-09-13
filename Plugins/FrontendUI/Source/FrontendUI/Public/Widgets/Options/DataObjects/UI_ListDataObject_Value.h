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

	void SetDataDynamicGetter(const TSharedPtr<FUI_OptionsDataInteractionHelper>& InDynamicGetter);
	void SetDataDynamicSetter(const TSharedPtr<FUI_OptionsDataInteractionHelper>& InDynamicSetter);
	
protected:

	TSharedPtr<FUI_OptionsDataInteractionHelper> DataDynamicGetter;
	TSharedPtr<FUI_OptionsDataInteractionHelper> DataDynamicSetter;
};
