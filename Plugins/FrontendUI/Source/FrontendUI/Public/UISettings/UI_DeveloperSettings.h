// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DeveloperSettings.h"
#include "UI_DeveloperSettings.generated.h"

class UUIWidget_ActivatableBase;

UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Frontend UI Settings"))
class FRONTENDUI_API UUI_DeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	UPROPERTY(Config, EditAnywhere, Category = "Widget Reference", meta = (ForceInlineRow, Categories = "Frontend.Widget"))
	TMap<FGameplayTag, TSoftClassPtr<UUIWidget_ActivatableBase>> FrontendWidgetMap; 
};
