﻿// Eduard Ciofu All Rights Reserved


#include "Widgets/Options/UI_OptionsDataRegistry.h"

#include "UI_BlueprintLibrary.h"
#include "UI_GameplayTags.h"
#include "UISettings/UI_GameUserSettings.h"
#include "Widgets/Options/UI_OptionsDataInteractionHelper.h"
#include "Widgets/Options/DataObjects/UI_ListDataObject_Collection.h"
#include "Widgets/Options/DataObjects/UI_ListDataObject_Scalar.h"
#include "Widgets/Options/DataObjects/UI_ListDataObject_String.h"
#include "Widgets/Options/DataObjects/UI_ListDataObject_StringResolution.h"

#define MAKE_OPTIONS_DATA_CONTROL(SetterOrGetterFuncName)																			\
	MakeShared<FUI_OptionsDataInteractionHelper>(GET_FUNCTION_NAME_STRING_CHECKED(UUI_GameUserSettings, SetterOrGetterFuncName))

void UUI_OptionsDataRegistry::InitOptionsDataRegistry(ULocalPlayer* InOwningLocalPlayer)
{
	InitGameplayCollectionTab();
	InitAudioCollectionTab();
	InitVideoCollectionTab();
	InitControlCollectionTab();
}

void UUI_OptionsDataRegistry::InitGameplayCollectionTab()
{
	UUI_ListDataObject_Collection* GameplayTabCollection = NewObject<UUI_ListDataObject_Collection>();
	GameplayTabCollection->SetDataID(FName(TEXT("GameplayTabCollection")));
	GameplayTabCollection->SetDataDisplayName(FText::FromString(TEXT("Gameplay")));
	
	// Game Difficulty
	{
		UUI_ListDataObject_String* GameDifficulty = NewObject<UUI_ListDataObject_String>();
		GameDifficulty->SetDataID(FName(TEXT("GameDifficulty")));
		GameDifficulty->SetDataDisplayName(FText::FromString(TEXT("Difficulty")));
		GameDifficulty->SetDescriptionRichText(FText::FromString(TEXT("Adjusts the difficulty of the game experience.\n\n<Bold>Easy:</> Focuses on the story experience. Provides the most relaxing combat.\n\n<Bold>Normal:</> Offers slightly harder combat experience.\n\n<Bold>Hard:</> Offers a much more challenging combat experience.\n\n<Bold>Very Hard:</> Provides the most challenging combat experience. Not recommended for first playthrough.")));
		GameDifficulty->AddDynamicOption(TEXT("Easy"), FText::FromString(TEXT("Easy")));
		GameDifficulty->AddDynamicOption(TEXT("Normal"), FText::FromString(TEXT("Normal")));
		GameDifficulty->AddDynamicOption(TEXT("Hard"), FText::FromString(TEXT("Hard")));
		GameDifficulty->AddDynamicOption(TEXT("Very Hard"), FText::FromString(TEXT("Very Hard")));
		GameDifficulty->SetDefaultValueFromString(TEXT("Normal"));
		GameDifficulty->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetCurrentGameDifficulty));
		GameDifficulty->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetCurrentGameDifficulty));
		GameDifficulty->SetShouldApplySettingsImmediately(true);

		GameplayTabCollection->AddChildListData(GameDifficulty);
	}

	// Test Item
	{
		UUI_ListDataObject_String* TestItem = NewObject<UUI_ListDataObject_String>();
		TestItem->SetDataID(FName(TEXT("TestItem")));
		TestItem->SetDataDisplayName(FText::FromString(TEXT("Test Image")));
		TestItem->SetSoftDescriptionImage(UUI_BlueprintLibrary::GetOptionsSoftImageByTag(Frontend::OptionsImages::TestImage));
		TestItem->SetDescriptionRichText(FText::FromString(TEXT("The image to display can be specified in the project settings. It can be anything the developer assigns there.")));

		GameplayTabCollection->AddChildListData(TestItem);
	}

	RegisteredOptionsTabCollections.Add(GameplayTabCollection);
}

void UUI_OptionsDataRegistry::InitAudioCollectionTab()
{
	UUI_ListDataObject_Collection* AudioTabCollection = NewObject<UUI_ListDataObject_Collection>();
	AudioTabCollection->SetDataID(FName(TEXT("AudioTabCollection")));
	AudioTabCollection->SetDataDisplayName(FText::FromString(TEXT("Audio")));

	// Volume Category
	{
		UUI_ListDataObject_Collection* VolumeCategoryCollection = NewObject<UUI_ListDataObject_Collection>();
		VolumeCategoryCollection->SetDataID(FName(TEXT("VolumeCategoryCollection")));
		VolumeCategoryCollection->SetDataDisplayName(FText::FromString(TEXT("Volume")));

		AudioTabCollection->AddChildListData(VolumeCategoryCollection);

		// Overall Volume
		{
			UUI_ListDataObject_Scalar* OverallVolume = NewObject<UUI_ListDataObject_Scalar>();
			OverallVolume->SetDataID(FName(TEXT("OverallVolume")));
			OverallVolume->SetDataDisplayName(FText::FromString(TEXT("Overall Volume")));
			OverallVolume->SetDescriptionRichText(FText::FromString(TEXT("This is a description for Overall Volume.")));
			OverallVolume->SetDisplayValueRange(TRange<float>(0.f, 1.f));
			OverallVolume->SetOutputValueRange(TRange<float>(0.f, 2.f));
			OverallVolume->SetSliderStepSize(0.01f);
			OverallVolume->SetDefaultValueFromString(LexToString(1.f));
			OverallVolume->SetDisplayNumericType(ECommonNumericType::Percentage);
			OverallVolume->SetNumberFormattingOptions(UUI_ListDataObject_Scalar::NoDecimal());
			OverallVolume->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetOverallVolume));
			OverallVolume->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetOverallVolume));
			OverallVolume->SetShouldApplySettingsImmediately(false);	// false to avoid lag spikes when moving the slider fast

			VolumeCategoryCollection->AddChildListData(OverallVolume);
		}

		// Music Volume
		{
			UUI_ListDataObject_Scalar* MusicVolume = NewObject<UUI_ListDataObject_Scalar>();
			MusicVolume->SetDataID(FName(TEXT("MusicVolume")));
			MusicVolume->SetDataDisplayName(FText::FromString(TEXT("Music Volume")));
			MusicVolume->SetDescriptionRichText(FText::FromString(TEXT("This is a description for Music Volume.")));
			MusicVolume->SetDisplayValueRange(TRange<float>(0.f, 1.f));
			MusicVolume->SetOutputValueRange(TRange<float>(0.f, 2.f));
			MusicVolume->SetSliderStepSize(0.01f);
			MusicVolume->SetDefaultValueFromString(LexToString(1.f));
			MusicVolume->SetDisplayNumericType(ECommonNumericType::Percentage);
			MusicVolume->SetNumberFormattingOptions(UUI_ListDataObject_Scalar::NoDecimal());
			MusicVolume->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetMusicVolume));
			MusicVolume->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetMusicVolume));
			MusicVolume->SetShouldApplySettingsImmediately(false);	// false to avoid lag spikes when moving the slider fast

			VolumeCategoryCollection->AddChildListData(MusicVolume);
		}

		// SFX Volume
		{
			UUI_ListDataObject_Scalar* SFXVolume = NewObject<UUI_ListDataObject_Scalar>();
			SFXVolume->SetDataID(FName(TEXT("SFXVolume")));
			SFXVolume->SetDataDisplayName(FText::FromString(TEXT("Sound Effects Volume")));
			SFXVolume->SetDescriptionRichText(FText::FromString(TEXT("This is a description for Sound Effects Volume.")));
			SFXVolume->SetDisplayValueRange(TRange<float>(0.f, 1.f));
			SFXVolume->SetOutputValueRange(TRange<float>(0.f, 2.f));
			SFXVolume->SetSliderStepSize(0.01f);
			SFXVolume->SetDefaultValueFromString(LexToString(1.f));
			SFXVolume->SetDisplayNumericType(ECommonNumericType::Percentage);
			SFXVolume->SetNumberFormattingOptions(UUI_ListDataObject_Scalar::NoDecimal());
			SFXVolume->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetSFXVolume));
			SFXVolume->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetSFXVolume));
			SFXVolume->SetShouldApplySettingsImmediately(false);	// false to avoid lag spikes when moving the slider fast

			VolumeCategoryCollection->AddChildListData(SFXVolume);
		}
	}

	// Sound Category
	{
		UUI_ListDataObject_Collection* SoundCategoryCollection = NewObject<UUI_ListDataObject_Collection>();
		SoundCategoryCollection->SetDataID(FName(TEXT("SoundCategoryCollection")));
		SoundCategoryCollection->SetDataDisplayName(FText::FromString(TEXT("Sound")));

		AudioTabCollection->AddChildListData(SoundCategoryCollection);

		// Background Audio
		{
			UUI_ListDataObject_StringBool* BackgroundAudio = NewObject<UUI_ListDataObject_StringBool>();
			BackgroundAudio->SetDataID(FName(TEXT("BackgroundAudio")));
			BackgroundAudio->SetDataDisplayName(FText::FromString(TEXT("Mute Background Audio")));
			BackgroundAudio->OverrideTrueDisplayText(FText::FromString(TEXT("Disabled")));
			BackgroundAudio->OverrideFalseDisplayText(FText::FromString(TEXT("Enabled")));
			BackgroundAudio->SetFalseAsDefaultValue();
			BackgroundAudio->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetBackgroundAudio));
			BackgroundAudio->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetBackgroundAudio));
			BackgroundAudio->SetShouldApplySettingsImmediately(true);

			SoundCategoryCollection->AddChildListData(BackgroundAudio);
		}

		// Use HDR Audio
		{
			UUI_ListDataObject_StringBool* HDRAudio = NewObject<UUI_ListDataObject_StringBool>();
			HDRAudio->SetDataID(FName(TEXT("HDRAudio")));
			HDRAudio->SetDataDisplayName(FText::FromString(TEXT("Use HDR Audio")));
			HDRAudio->OverrideTrueDisplayText(FText::FromString(TEXT("Enabled")));
			HDRAudio->OverrideFalseDisplayText(FText::FromString(TEXT("Disabled")));
			HDRAudio->SetFalseAsDefaultValue();
			HDRAudio->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetHDRAudio));
			HDRAudio->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetHDRAudio));
			HDRAudio->SetShouldApplySettingsImmediately(true);

			SoundCategoryCollection->AddChildListData(HDRAudio);
		}
	}
	
	RegisteredOptionsTabCollections.Add(AudioTabCollection);
}

void UUI_OptionsDataRegistry::InitVideoCollectionTab()
{
	UUI_ListDataObject_Collection* VideoTabCollection = NewObject<UUI_ListDataObject_Collection>();
	VideoTabCollection->SetDataID(FName(TEXT("VideoTabCollection")));
	VideoTabCollection->SetDataDisplayName(FText::FromString(TEXT("Video")));

	UUI_ListDataObject_StringEnum* CreatedWindowMode = nullptr;

	// Display Category
	{
		UUI_ListDataObject_Collection* DisplayCategoryCollection = NewObject<UUI_ListDataObject_Collection>();
		DisplayCategoryCollection->SetDataID(FName(TEXT("DisplayCategoryCollection")));
		DisplayCategoryCollection->SetDataDisplayName(FText::FromString(TEXT("Display")));

		VideoTabCollection->AddChildListData(DisplayCategoryCollection);

		FOptionsDataEditConditionDescriptor PackagedBuildOnlyCondition;
		PackagedBuildOnlyCondition.SetEditConditionFunc([]()->bool
			{
				const bool bIsInEditor = GIsEditor || GIsPlayInEditorWorld;

				return !bIsInEditor;
			}
		);
		PackagedBuildOnlyCondition.SetDisabledRichReason(TEXT("\n\n<Disabled>This setting can only be adjusted in a packaged build.</>"));

		// Window Mode
		{
			UUI_ListDataObject_StringEnum* WindowMode = NewObject<UUI_ListDataObject_StringEnum>();
			WindowMode->SetDataID(FName(TEXT("WindowMode")));
			WindowMode->SetDataDisplayName(FText::FromString(TEXT("Window Mode")));
			WindowMode->SetDescriptionRichText(FText::FromString(TEXT("This is a description for Window Mode")));
			WindowMode->AddEnumOption(EWindowMode::Fullscreen, FText::FromString(TEXT("Fullscreen")));
			WindowMode->AddEnumOption(EWindowMode::WindowedFullscreen, FText::FromString(TEXT("Borderless Window")));
			WindowMode->AddEnumOption(EWindowMode::Windowed, FText::FromString(TEXT("Windowed")));
			WindowMode->SetDefaultValueFromEnumOption(EWindowMode::WindowedFullscreen);
			WindowMode->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetFullscreenMode));
			WindowMode->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetFullscreenMode));
			WindowMode->SetShouldApplySettingsImmediately(true);

			WindowMode->AddEditCondition(PackagedBuildOnlyCondition);
			VideoTabCollection->AddChildListData(WindowMode);
			CreatedWindowMode = WindowMode;
		}

		// Screen Resolution
		{
			UUI_ListDataObject_StringResolution* ScreenResolution = NewObject<UUI_ListDataObject_StringResolution>();
			ScreenResolution->SetDataID(FName(TEXT("ScreenResolution")));
			ScreenResolution->SetDataDisplayName(FText::FromString(TEXT("Resolution")));
			ScreenResolution->SetDescriptionRichText(FText::FromString(TEXT("This is a description for Resolution")));
			ScreenResolution->InitResolutionValues();
			ScreenResolution->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetScreenResolution));
			ScreenResolution->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetScreenResolution));
			ScreenResolution->SetShouldApplySettingsImmediately(true);

			FOptionsDataEditConditionDescriptor WindowModeEditCondition;
			WindowModeEditCondition.SetEditConditionFunc([CreatedWindowMode]()->bool
				{
					const bool bIsBorderlessWindow = CreatedWindowMode->GetCurrentValueAsEnum<EWindowMode::Type>() == EWindowMode::WindowedFullscreen;

					return !bIsBorderlessWindow;
				}
			);
			WindowModeEditCondition.SetDisabledRichReason(TEXT("\n\n<Disabled>Screen Resolution is not adjustable when in Borderless Window mode.</>"));
			WindowModeEditCondition.SetDisabledForcedStringValue(ScreenResolution->GetMaximumAllowedResolution());

			ScreenResolution->AddEditCondition(WindowModeEditCondition);
			ScreenResolution->AddEditCondition(PackagedBuildOnlyCondition);
			ScreenResolution->AddEditDependencyData(CreatedWindowMode);
			VideoTabCollection->AddChildListData(ScreenResolution);
		}

		// Display Gamma
		{
			UUI_ListDataObject_Scalar* DisplayGamma = NewObject<UUI_ListDataObject_Scalar>();
			DisplayGamma->SetDataID(FName(TEXT("DisplayGamma")));
			DisplayGamma->SetDataDisplayName(FText::FromString(TEXT("Display Gamma")));
			DisplayGamma->SetDescriptionRichText(FText::FromString(TEXT("This is a description for Display Gamma")));
			DisplayGamma->SetDisplayValueRange(TRange<float>(0.f, 1.f));
			DisplayGamma->SetOutputValueRange(TRange<float>(1.7f, 2.7f));	// The default value in Unreal is 2.2f
			DisplayGamma->SetDisplayNumericType(ECommonNumericType::Percentage);
			DisplayGamma->SetNumberFormattingOptions(UUI_ListDataObject_Scalar::NoDecimal());
			DisplayGamma->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetCurrentDisplayGamma));
			DisplayGamma->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetCurrentDisplayGamma));
			DisplayGamma->SetDefaultValueFromString(LexToString(2.2f));

			DisplayGamma->AddEditCondition(PackagedBuildOnlyCondition);
			VideoTabCollection->AddChildListData(DisplayGamma);
		}
	}

	// Graphics Category
	{
		UUI_ListDataObject_Collection* GraphicsCategoryCollection = NewObject<UUI_ListDataObject_Collection>();
		GraphicsCategoryCollection->SetDataID(FName(TEXT("GraphicsCategory")));
		GraphicsCategoryCollection->SetDataDisplayName(FText::FromString(TEXT("Graphics")));
		
		VideoTabCollection->AddChildListData(GraphicsCategoryCollection);

		{
			UUI_ListDataObject_StringInteger* OverallQuality = NewObject<UUI_ListDataObject_StringInteger>();
			OverallQuality->SetDataID(FName(TEXT("OverallQuality")));
			OverallQuality->SetDataDisplayName(FText::FromString(TEXT("Overall Quality")));
			OverallQuality->SetDescriptionRichText(FText::FromString(TEXT("This is a description for Overall Quality")));
			OverallQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
			OverallQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
			OverallQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
			OverallQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
			OverallQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			OverallQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetOverallScalabilityLevel));
			OverallQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetOverallScalabilityLevel));
			OverallQuality->SetShouldApplySettingsImmediately(true);

			GraphicsCategoryCollection->AddChildListData(OverallQuality);
		}
	}

	RegisteredOptionsTabCollections.Add(VideoTabCollection);
}

void UUI_OptionsDataRegistry::InitControlCollectionTab()
{
	UUI_ListDataObject_Collection* ControlTabCollection = NewObject<UUI_ListDataObject_Collection>();
	ControlTabCollection->SetDataID(FName(TEXT("ControlTabCollection")));
	ControlTabCollection->SetDataDisplayName(FText::FromString(TEXT("Control")));

	RegisteredOptionsTabCollections.Add(ControlTabCollection);
}

TArray<UUI_ListDataObject_Base*> UUI_OptionsDataRegistry::GetListSourceItemsBySelectedTabID(const FName& InSelectedTabID) const
{
	const UUI_ListDataObject_Collection* FoundTabCollection = RegisteredOptionsTabCollections.FindByPredicate(
		[InSelectedTabID](const UUI_ListDataObject_Collection* AvailableTabCollection)->bool
		{
			return AvailableTabCollection->GetDataID() == InSelectedTabID;
		}
	)->Get();
	checkf(FoundTabCollection, TEXT("No valid tab found under the ID %s"), *InSelectedTabID.ToString());

	TArray<UUI_ListDataObject_Base*> AllChildListItems;
	FindChildListDataRecursively(FoundTabCollection, AllChildListItems);

	return AllChildListItems;
}

void UUI_OptionsDataRegistry::FindChildListDataRecursively(const UUI_ListDataObject_Base* InParentData, TArray<UUI_ListDataObject_Base*>& OutFoundChildListData) const
{
	if (!IsValid(InParentData) || !InParentData->HasAnyChildListData()) return;

	for (UUI_ListDataObject_Base* SubChildListData : InParentData->GetAllChildListData())
	{
		if (!SubChildListData) continue;

		OutFoundChildListData.Add(SubChildListData);
		if (SubChildListData->HasAnyChildListData())
		{
			FindChildListDataRecursively(SubChildListData, OutFoundChildListData);
		}
	}
}
