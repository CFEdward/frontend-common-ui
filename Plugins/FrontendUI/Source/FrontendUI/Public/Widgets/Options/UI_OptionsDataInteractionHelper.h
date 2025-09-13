// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "PropertyPathHelpers.h"

class UUI_GameUserSettings;

class FRONTENDUI_API FUI_OptionsDataInteractionHelper
{
public:

	FUI_OptionsDataInteractionHelper(const FString& InSetterOrGetterFuncPath);

	FString GetValueAsString() const;
	void SetValueFromString(const FString& InStringValue);
	
private:

	FCachedPropertyPath CachedDynamicFunctionPath;

	TWeakObjectPtr<UUI_GameUserSettings> CachedWeakGameUserSettings;
};
