// Eduard Ciofu All Rights Reserved


#include "Widgets/Options/DataObjects/UI_ListDataObject_StringResolution.h"

#include "Kismet/KismetSystemLibrary.h"
#include "UISettings/UI_GameUserSettings.h"

void UUI_ListDataObject_StringResolution::InitResolutionValues()
{
	TArray<FIntPoint> AvailableScreenResolutions;
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(AvailableScreenResolutions);
	AvailableScreenResolutions.Sort([](const FIntPoint& A, const FIntPoint& B)->bool
		{
			return A.SizeSquared() < B.SizeSquared();
		}
	);
	
	for (const FIntPoint& Resolution : AvailableScreenResolutions)
	{
		AddDynamicOption(ResToValueString(Resolution), ResToDisplayText(Resolution));
	}

	MaximumAllowedResolution = ResToValueString(AvailableScreenResolutions.Last());
	SetDefaultValueFromString(MaximumAllowedResolution);
}

void UUI_ListDataObject_StringResolution::OnDataObjectInitialized()
{
	Super::OnDataObjectInitialized();

	if (!TrySetDisplayTextFromStringValue(CurrentStringValue))
	{
		CurrentDisplayText = ResToDisplayText(UUI_GameUserSettings::Get()->GetScreenResolution());
	}
}

FString UUI_ListDataObject_StringResolution::ResToValueString(const FIntPoint& InResolution) const
{
	// (X=2560,Y=1440)
	return FString::Printf(TEXT("(X=%i,Y=%i)"), InResolution.X, InResolution.Y);
}

FText UUI_ListDataObject_StringResolution::ResToDisplayText(const FIntPoint& InResolution) const
{
	// X=2560 Y=1440
	return FText::FromString(FString::Printf(TEXT("%i x %i"), InResolution.X, InResolution.Y));
}
