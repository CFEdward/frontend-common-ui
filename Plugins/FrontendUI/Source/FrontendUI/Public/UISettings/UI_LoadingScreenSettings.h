// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "UI_LoadingScreenSettings.generated.h"

UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Frontend Loading Screen Settings"))
class FRONTENDUI_API UUI_LoadingScreenSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	
	TSubclassOf<UUserWidget> GetLoadingScreenWidgetClassChecked() const;
	
	UPROPERTY(Config, EditAnywhere, Category = "Loading Screen Settings")
	TSoftClassPtr<UUserWidget> SoftLoadingScreenWidgetClass;
	
	UPROPERTY(Config, EditAnywhere, Category = "Loading Screen Settings")
	float HoldLoadingScreenExtraSeconds{ 3.f };
	
	UPROPERTY(Config, EditAnywhere, Category = "Loading Screen Settings")
	bool bShowLoadingScreenInEditor{ false };
};
