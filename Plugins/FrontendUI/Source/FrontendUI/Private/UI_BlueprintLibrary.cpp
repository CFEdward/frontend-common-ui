// Eduard Ciofu All Rights Reserved


#include "UI_BlueprintLibrary.h"

#include "UISettings/UI_DeveloperSettings.h"

TSoftClassPtr<UUIWidget_ActivatableBase> UUI_BlueprintLibrary::GetFrontendSoftWidgetClassByTag(const FGameplayTag InWidgetTag)
{
	const UUI_DeveloperSettings* UIDeveloperSettings = GetDefault<UUI_DeveloperSettings>();
	checkf(UIDeveloperSettings->FrontendWidgetMap.Contains(InWidgetTag), TEXT("Could not find the corresponding widget under the tag %s"), *InWidgetTag.ToString());

	return UIDeveloperSettings->FrontendWidgetMap.FindRef(InWidgetTag);
}

TSoftObjectPtr<UTexture2D> UUI_BlueprintLibrary::GetOptionsSoftImageByTag(FGameplayTag InImageTag)
{
	const UUI_DeveloperSettings* UIDeveloperSettings = GetDefault<UUI_DeveloperSettings>();
	checkf(UIDeveloperSettings->OptionsScreenSoftImageMap.Contains(InImageTag), TEXT("Could not find an image associated with the tag %s"), *InImageTag.ToString());

	return UIDeveloperSettings->OptionsScreenSoftImageMap.FindRef(InImageTag);
}
