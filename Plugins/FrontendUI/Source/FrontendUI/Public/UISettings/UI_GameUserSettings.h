// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "UI_GameUserSettings.generated.h"

UCLASS()
class FRONTENDUI_API UUI_GameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:

	static UUI_GameUserSettings* Get();

private:

	UPROPERTY(Config)
	FString CurrentGameDifficulty;
};
