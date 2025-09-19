// Eduard Ciofu All Rights Reserved


#include "UISettings/UI_GameUserSettings.h"

UUI_GameUserSettings::UUI_GameUserSettings()
	: OverallVolume(1.f)
{
}

UUI_GameUserSettings* UUI_GameUserSettings::Get()
{
	if (GEngine)
	{
		return CastChecked<UUI_GameUserSettings>(GEngine->GetGameUserSettings());
	}

	return nullptr;
}

void UUI_GameUserSettings::SetOverallVolume(const float InVolume)
{
	OverallVolume = InVolume;

	// The actual logic for controlling the volume goes here
}
