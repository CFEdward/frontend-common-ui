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
