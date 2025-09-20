// Eduard Ciofu All Rights Reserved


#include "UISettings/UI_GameUserSettings.h"

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

void UUI_GameUserSettings::SetMusicVolume(const float InVolume)
{
	MusicVolume = InVolume;

	// ...
}

void UUI_GameUserSettings::SetSFXVolume(const float InVolume)
{
	SFXVolume = InVolume;

	// ...
}

void UUI_GameUserSettings::SetBackgroundAudio(const bool bInBackgroundAudio)
{
	bBackgroundAudio = bInBackgroundAudio;

	// ...
}

void UUI_GameUserSettings::SetHDRAudio(const bool bInHDRAudio)
{
	bHDRAudio = bInHDRAudio;

	// ...
}
