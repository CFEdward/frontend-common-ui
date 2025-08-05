// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UI_ListDataObject_Value.h"
#include "UI_ListDataObject_String.generated.h"

UCLASS()
class FRONTENDUI_API UUI_ListDataObject_String : public UUI_ListDataObject_Value
{
	GENERATED_BODY()

public:

	void AddDynamicOption(const FString& InStringValue, const FText& InDisplayText);
	
protected:

	FString CurrentStringValue;
	FText CurrentDisplayText;
	TArray<FString> AvailableOptionsStringArray;
	TArray<FText> AvailableOptionsTextArray;
};
