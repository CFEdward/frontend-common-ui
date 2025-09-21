// Eduard Ciofu All Rights Reserved


#include "Widgets/Options/DataObjects/UI_ListDataObject_StringResolution.h"

#include "UI_DebugHelper.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Widgets/Options/UI_OptionsDataInteractionHelper.h"

void UUI_ListDataObject_StringResolution::InitResolutionValues()
{
	TArray<FIntPoint> AvailableScreenResolutions;
	// X=2560 Y=1440
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(AvailableScreenResolutions);
	for (const FIntPoint& Resolution : AvailableScreenResolutions)
	{
		// (X=2560,Y=1440)
		Debug::Print(TEXT("Available Resolution: ") + Resolution.ToString());
	}
}

void UUI_ListDataObject_StringResolution::OnDataObjectInitialized()
{
	Super::OnDataObjectInitialized();

	if (DataDynamicGetter)
	{
		Debug::Print(TEXT("Resolution Value from Dynamic Getter: ") + DataDynamicGetter->GetValueAsString());
	}
}
