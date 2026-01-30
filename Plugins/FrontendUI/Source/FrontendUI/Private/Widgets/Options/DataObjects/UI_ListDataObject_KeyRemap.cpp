// Eduard Ciofu All Rights Reserved


#include "Widgets/Options/DataObjects/UI_ListDataObject_KeyRemap.h"

#include "CommonInputBaseTypes.h"
#include "CommonInputSubsystem.h"
#include "UI_DebugHelper.h"

void UUI_ListDataObject_KeyRemap::InitKeyRemapData(UEnhancedInputUserSettings* InOwningInputUserSettings,
                                                   UEnhancedPlayerMappableKeyProfile* InKeyProfile, const ECommonInputType InDesiredInputKeyType, const FPlayerKeyMapping& InOwningPlayerKeyMapping)
{
	CachedOwningInputUserSettings = InOwningInputUserSettings;
	CachedOwningKeyProfile = InKeyProfile;
	CachedDesiredInputKeyType = InDesiredInputKeyType;
	CachedOwningMappingName = InOwningPlayerKeyMapping.GetMappingName();
	CachedOwningMappableKeySlot = InOwningPlayerKeyMapping.GetSlot();
}

FSlateBrush UUI_ListDataObject_KeyRemap::GetIconFromCurrentKey() const
{
	check(CachedOwningInputUserSettings);
	
	FSlateBrush FoundBrush;
	const UCommonInputSubsystem* CommonInputSubsystem = UCommonInputSubsystem::Get(CachedOwningInputUserSettings->GetLocalPlayer());
	check(CommonInputSubsystem);
	
	const bool bHasFoundBrush = UCommonInputPlatformSettings::Get()->TryGetInputBrush(
		FoundBrush,
		GetOwningKeyMapping()->GetCurrentKey(),
		CachedDesiredInputKeyType,
		CommonInputSubsystem->GetCurrentGamepadName()
	);
	
	if (!bHasFoundBrush)
	{
		Debug::Print(
			TEXT("Unable to find an icon for the key ") +
			GetOwningKeyMapping()->GetCurrentKey().GetDisplayName().ToString() +
			TEXT(" Empty brush was applied.")
		);
	}
	
	return FoundBrush;
}

FPlayerKeyMapping* UUI_ListDataObject_KeyRemap::GetOwningKeyMapping() const
{
	check(CachedOwningKeyProfile);
	
	FMapPlayerKeyArgs KeyArgs;
	KeyArgs.MappingName = CachedOwningMappingName;
	KeyArgs.Slot = CachedOwningMappableKeySlot;
	
	return CachedOwningKeyProfile->FindKeyMapping(KeyArgs);
}