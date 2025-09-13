// Eduard Ciofu All Rights Reserved


#include "Widgets/Options/UI_OptionsDataInteractionHelper.h"

#include "UISettings/UI_GameUserSettings.h"

FUI_OptionsDataInteractionHelper::FUI_OptionsDataInteractionHelper(const FString& InSetterOrGetterFuncPath)
	: CachedDynamicFunctionPath(InSetterOrGetterFuncPath)
{
	CachedWeakGameUserSettings = UUI_GameUserSettings::Get();
}

FString FUI_OptionsDataInteractionHelper::GetValueAsString() const
{
	FString OutStringValue;
	PropertyPathHelpers::GetPropertyValueAsString(CachedWeakGameUserSettings.Get(), CachedDynamicFunctionPath, OutStringValue);

	return OutStringValue;
}

void FUI_OptionsDataInteractionHelper::SetValueFromString(const FString& InStringValue)
{
	PropertyPathHelpers::SetPropertyValueFromString(CachedWeakGameUserSettings.Get(), CachedDynamicFunctionPath, InStringValue);
}
