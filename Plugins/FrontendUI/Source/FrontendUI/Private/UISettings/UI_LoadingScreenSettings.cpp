// Eduard Ciofu All Rights Reserved


#include "UISettings/UI_LoadingScreenSettings.h"

#include "Blueprint/UserWidget.h"

TSubclassOf<UUserWidget> UUI_LoadingScreenSettings::GetLoadingScreenWidgetClassChecked() const
{
	checkf(!SoftLoadingScreenWidgetClass.IsNull(), TEXT("Forgot to assign a valid Widget Blueprint in the Project Settings as a loading screen!"));
	
	TSubclassOf<UUserWidget> LoadedLoadingScreenWidget = SoftLoadingScreenWidgetClass.LoadSynchronous();
	
	return LoadedLoadingScreenWidget;
}
