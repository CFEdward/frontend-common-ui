// Eduard Ciofu All Rights Reserved


#include "Widgets/Options/DataObjects/UI_ListDataObject_Value.h"

void UUI_ListDataObject_Value::SetDataDynamicGetter(const TSharedPtr<FUI_OptionsDataInteractionHelper>& InDynamicGetter)
{
	DataDynamicGetter = InDynamicGetter;
}

void UUI_ListDataObject_Value::SetDataDynamicSetter(const TSharedPtr<FUI_OptionsDataInteractionHelper>& InDynamicSetter)
{
	DataDynamicSetter = InDynamicSetter;
}
