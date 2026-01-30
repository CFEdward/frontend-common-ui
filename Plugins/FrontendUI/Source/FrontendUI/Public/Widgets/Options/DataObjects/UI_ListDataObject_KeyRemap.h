// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonInputTypeEnum.h"
#include "UI_ListDataObject_Base.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "UI_ListDataObject_KeyRemap.generated.h"

class UEnhancedPlayerMappableKeyProfile;
class UEnhancedInputUserSettings;

UCLASS()
class FRONTENDUI_API UUI_ListDataObject_KeyRemap : public UUI_ListDataObject_Base
{
	GENERATED_BODY()
	
public:
	
	void InitKeyRemapData(UEnhancedInputUserSettings* InOwningInputUserSettings, UEnhancedPlayerMappableKeyProfile* InKeyProfile, ECommonInputType InDesiredInputKeyType, const FPlayerKeyMapping& InOwningPlayerKeyMapping);
	
	FSlateBrush GetIconFromCurrentKey() const;
	
private:
	
	FPlayerKeyMapping* GetOwningKeyMapping() const;
	
	UPROPERTY(Transient)
	TObjectPtr<UEnhancedInputUserSettings> CachedOwningInputUserSettings;
	UPROPERTY(Transient)
	TObjectPtr<UEnhancedPlayerMappableKeyProfile> CachedOwningKeyProfile;
	
	ECommonInputType CachedDesiredInputKeyType;
	
	FName CachedOwningMappingName;
	
	EPlayerMappableKeySlot CachedOwningMappableKeySlot;
};
