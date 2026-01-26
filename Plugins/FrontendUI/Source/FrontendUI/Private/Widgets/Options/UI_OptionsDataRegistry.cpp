// Eduard Ciofu All Rights Reserved


#include "Widgets/Options/UI_OptionsDataRegistry.h"

#include "UI_BlueprintLibrary.h"
#include "UI_GameplayTags.h"
#include "Internationalization/StringTableRegistry.h"
#include "UISettings/UI_GameUserSettings.h"
#include "Widgets/Options/UI_OptionsDataInteractionHelper.h"
#include "Widgets/Options/DataObjects/UI_ListDataObject_Collection.h"
#include "Widgets/Options/DataObjects/UI_ListDataObject_Scalar.h"
#include "Widgets/Options/DataObjects/UI_ListDataObject_String.h"
#include "Widgets/Options/DataObjects/UI_ListDataObject_StringResolution.h"

#define MAKE_OPTIONS_DATA_CONTROL(SetterOrGetterFuncName)	\
	MakeShared<FUI_OptionsDataInteractionHelper>(GET_FUNCTION_NAME_STRING_CHECKED(UUI_GameUserSettings, SetterOrGetterFuncName))

#define GET_DESCRIPTION(InKey)	\
	LOCTABLE("/FrontendUI/UI/StringTables/ST_OptionsScreenDescription.ST_OptionsScreenDescription", InKey)

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
			WindowMode->SetDescriptionRichText(GET_DESCRIPTION("WindowModeDescKey"));
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
			ScreenResolution->SetDescriptionRichText(GET_DESCRIPTION("ScreenResolutionsDescKey"));
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
		
		//Vertical Sync
		{
			UUI_ListDataObject_StringBool* VerticalSync = NewObject<UUI_ListDataObject_StringBool>();
			VerticalSync->SetDataID(FName("VerticalSync"));
			VerticalSync->SetDataDisplayName(FText::FromString(TEXT("V-Sync")));
			VerticalSync->SetDescriptionRichText(GET_DESCRIPTION("VerticalSyncDescKey"));
			VerticalSync->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(IsVSyncEnabled));
			VerticalSync->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetVSyncEnabled));
			VerticalSync->SetFalseAsDefaultValue();
			VerticalSync->SetShouldApplySettingsImmediately(true);

			FOptionsDataEditConditionDescriptor FullscreenOnlyCondition;
			FullscreenOnlyCondition.SetEditConditionFunc(
				[CreatedWindowMode]()->bool
				{
					return CreatedWindowMode->GetCurrentValueAsEnum<EWindowMode::Type>() == EWindowMode::Fullscreen;
				}
			);
			FullscreenOnlyCondition.SetDisabledRichReason(TEXT("\n\n<Disabled>This feature only works if the 'Window Mode' is set to 'Fullscreen'.</>"));
			FullscreenOnlyCondition.SetDisabledForcedStringValue(TEXT("false"));

			VerticalSync->AddEditCondition(FullscreenOnlyCondition);
			VideoTabCollection->AddChildListData(VerticalSync);
		}
		
		// Frame Rate Limit
		{
			UUI_ListDataObject_String* FrameRateLimit = NewObject<UUI_ListDataObject_String>();
			FrameRateLimit->SetDataID(FName(TEXT("FrameRateLimit")));
			FrameRateLimit->SetDataDisplayName(FText::FromString(TEXT("Frame Rate Limit")));
			FrameRateLimit->SetDescriptionRichText(GET_DESCRIPTION("FrameRateLimitDescKey"));
			FrameRateLimit->AddDynamicOption(LexToString(30.f), FText::FromString(TEXT("30 FPS")));
			FrameRateLimit->AddDynamicOption(LexToString(60.f), FText::FromString(TEXT("60 FPS")));
			FrameRateLimit->AddDynamicOption(LexToString(90.f), FText::FromString(TEXT("90 FPS")));
			FrameRateLimit->AddDynamicOption(LexToString(120.f), FText::FromString(TEXT("120 FPS")));
			FrameRateLimit->AddDynamicOption(LexToString(0.f), FText::FromString(TEXT("No Limit")));
			FrameRateLimit->SetDefaultValueFromString(LexToString(0.f));
			FrameRateLimit->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetFrameRateLimit));
			FrameRateLimit->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetFrameRateLimit));
			FrameRateLimit->SetShouldApplySettingsImmediately(true);
			
			VideoTabCollection->AddChildListData(FrameRateLimit);
		}

		// Display Gamma
		{
			UUI_ListDataObject_Scalar* DisplayGamma = NewObject<UUI_ListDataObject_Scalar>();
			DisplayGamma->SetDataID(FName(TEXT("DisplayGamma")));
			DisplayGamma->SetDataDisplayName(FText::FromString(TEXT("Display Gamma")));
			DisplayGamma->SetDescriptionRichText(GET_DESCRIPTION("DisplayGammaDescKey"));
			DisplayGamma->SetDisplayValueRange(TRange<float>(0.f, 1.f));
			DisplayGamma->SetOutputValueRange(TRange<float>(1.7f, 2.7f));	// The default value in Unreal is 2.2f
			DisplayGamma->SetSliderStepSize(.01f);
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

		UUI_ListDataObject_StringInteger* CreatedOverallQuality = nullptr;
		
		// Overall Quality
		{
			UUI_ListDataObject_StringInteger* OverallQuality = NewObject<UUI_ListDataObject_StringInteger>();
			OverallQuality->SetDataID(FName(TEXT("OverallQuality")));
			OverallQuality->SetDataDisplayName(FText::FromString(TEXT("Overall Quality")));
			OverallQuality->SetDescriptionRichText(GET_DESCRIPTION("OverallQualityDescKey"));
			OverallQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
			OverallQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
			OverallQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
			OverallQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
			OverallQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			OverallQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetOverallScalabilityLevel));
			OverallQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetOverallScalabilityLevel));
			OverallQuality->SetShouldApplySettingsImmediately(true);

			CreatedOverallQuality = OverallQuality;
			GraphicsCategoryCollection->AddChildListData(OverallQuality);
		}

		// Resolution Scale
		{
			UUI_ListDataObject_Scalar* ResolutionScale = NewObject<UUI_ListDataObject_Scalar>();
			ResolutionScale->SetDataID(FName(TEXT("ResolutionScale")));
			ResolutionScale->SetDataDisplayName(FText::FromString(TEXT("3D Resolution")));
			ResolutionScale->SetDescriptionRichText(GET_DESCRIPTION("ResolutionScaleDescKey"));
			ResolutionScale->SetDisplayValueRange(TRange<float>(0.f, 1.f));
			ResolutionScale->SetOutputValueRange(TRange<float>(0.f, 1.f));
			ResolutionScale->SetSliderStepSize(.01f); 
			ResolutionScale->SetDisplayNumericType(ECommonNumericType::Percentage);
			ResolutionScale->SetNumberFormattingOptions(UUI_ListDataObject_Scalar::NoDecimal());
			ResolutionScale->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetResolutionScaleNormalized));
			ResolutionScale->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetResolutionScaleNormalized));
			ResolutionScale->SetShouldApplySettingsImmediately(false);

			ResolutionScale->AddEditDependencyData(CreatedOverallQuality);
			GraphicsCategoryCollection->AddChildListData(ResolutionScale);
		}
		
		// Global Illumination Quality
		{
		    UUI_ListDataObject_StringInteger* GIQuality = NewObject<UUI_ListDataObject_StringInteger>();
		    GIQuality->SetDataID(FName(TEXT("GIQuality")));
            GIQuality->SetDataDisplayName(FText::FromString(TEXT("Global Illumination Quality")));
            GIQuality->SetDescriptionRichText(GET_DESCRIPTION("GlobalIlluminationQualityDescKey"));
            GIQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
            GIQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
            GIQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
            GIQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
            GIQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
            GIQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetGlobalIlluminationQuality));
            GIQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetGlobalIlluminationQuality));
            GIQuality->SetShouldApplySettingsImmediately(true);
            
            GIQuality->AddEditDependencyData(CreatedOverallQuality);
            CreatedOverallQuality->AddEditDependencyData(GIQuality);
            GraphicsCategoryCollection->AddChildListData(GIQuality);
		}

		// Shadow Quality
		{
			UUI_ListDataObject_StringInteger* ShadowQuality = NewObject<UUI_ListDataObject_StringInteger>();
			ShadowQuality->SetDataID(FName(TEXT("ShadowQuality")));
			ShadowQuality->SetDataDisplayName(FText::FromString(TEXT("Shadow Quality")));
			ShadowQuality->SetDescriptionRichText(GET_DESCRIPTION("ShadowQualityDescKey"));
			ShadowQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
			ShadowQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
			ShadowQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
			ShadowQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
			ShadowQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			ShadowQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetShadowQuality));
			ShadowQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetShadowQuality));
			ShadowQuality->SetShouldApplySettingsImmediately(true);
            
			ShadowQuality->AddEditDependencyData(CreatedOverallQuality);
			CreatedOverallQuality->AddEditDependencyData(ShadowQuality);
			GraphicsCategoryCollection->AddChildListData(ShadowQuality);
		}

		// Anti-Aliasing Quality
		{
			UUI_ListDataObject_StringInteger* AAQuality = NewObject<UUI_ListDataObject_StringInteger>();
			AAQuality->SetDataID(FName(TEXT("AAQuality")));
			AAQuality->SetDataDisplayName(FText::FromString(TEXT("Anti Aliasing Quality")));
			AAQuality->SetDescriptionRichText(GET_DESCRIPTION("AntiAliasingDescKey"));
			AAQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
			AAQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
			AAQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
			AAQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
			AAQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			AAQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetAntiAliasingQuality));
			AAQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetAntiAliasingQuality));
			AAQuality->SetShouldApplySettingsImmediately(true);
            
			AAQuality->AddEditDependencyData(CreatedOverallQuality);
			CreatedOverallQuality->AddEditDependencyData(AAQuality);
			GraphicsCategoryCollection->AddChildListData(AAQuality);
		}

		// View Distance Quality
		{
			UUI_ListDataObject_StringInteger* ViewDistanceQuality = NewObject<UUI_ListDataObject_StringInteger>();
			ViewDistanceQuality->SetDataID(FName(TEXT("ViewDistanceQuality")));
			ViewDistanceQuality->SetDataDisplayName(FText::FromString(TEXT("View Distance")));
			ViewDistanceQuality->SetDescriptionRichText(GET_DESCRIPTION("ViewDistanceDescKey"));
			ViewDistanceQuality->AddIntegerOption(0, FText::FromString(TEXT("Near")));
			ViewDistanceQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
			ViewDistanceQuality->AddIntegerOption(2, FText::FromString(TEXT("Far")));
			ViewDistanceQuality->AddIntegerOption(3, FText::FromString(TEXT("Very Far")));
			ViewDistanceQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			ViewDistanceQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetViewDistanceQuality));
			ViewDistanceQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetViewDistanceQuality));
			ViewDistanceQuality->SetShouldApplySettingsImmediately(true);
            
			ViewDistanceQuality->AddEditDependencyData(CreatedOverallQuality);
			CreatedOverallQuality->AddEditDependencyData(ViewDistanceQuality);
			GraphicsCategoryCollection->AddChildListData(ViewDistanceQuality);
		}

		// Texture Quality
		{
			UUI_ListDataObject_StringInteger* TextureQuality = NewObject<UUI_ListDataObject_StringInteger>();
			TextureQuality->SetDataID(FName(TEXT("TextureQuality")));
			TextureQuality->SetDataDisplayName(FText::FromString(TEXT("Texture Quality")));
			TextureQuality->SetDescriptionRichText(GET_DESCRIPTION("TextureQualityDescKey"));
			TextureQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
			TextureQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
			TextureQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
			TextureQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
			TextureQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			TextureQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetTextureQuality));
			TextureQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetTextureQuality));
			TextureQuality->SetShouldApplySettingsImmediately(true);
            
			TextureQuality->AddEditDependencyData(CreatedOverallQuality);
			CreatedOverallQuality->AddEditDependencyData(TextureQuality);
			GraphicsCategoryCollection->AddChildListData(TextureQuality);
		}

		// Visual Effects Quality
		{
			UUI_ListDataObject_StringInteger* VisualEffectQuality = NewObject<UUI_ListDataObject_StringInteger>();
			VisualEffectQuality->SetDataID(FName(TEXT("VisualEffectQuality")));
			VisualEffectQuality->SetDataDisplayName(FText::FromString(TEXT("Visual Effects Quality")));
			VisualEffectQuality->SetDescriptionRichText(GET_DESCRIPTION("VisualEffectQualityDescKey"));
			VisualEffectQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
			VisualEffectQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
			VisualEffectQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
			VisualEffectQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
			VisualEffectQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			VisualEffectQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetVisualEffectQuality));
			VisualEffectQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetVisualEffectQuality));
			VisualEffectQuality->SetShouldApplySettingsImmediately(true);
            
			VisualEffectQuality->AddEditDependencyData(CreatedOverallQuality);
			CreatedOverallQuality->AddEditDependencyData(VisualEffectQuality);
			GraphicsCategoryCollection->AddChildListData(VisualEffectQuality);
		}

		// Reflection Quality
		{
			UUI_ListDataObject_StringInteger* ReflectionQuality = NewObject<UUI_ListDataObject_StringInteger>();
			ReflectionQuality->SetDataID(FName(TEXT("ReflectionQuality")));
			ReflectionQuality->SetDataDisplayName(FText::FromString(TEXT("Reflection Quality")));
			ReflectionQuality->SetDescriptionRichText(GET_DESCRIPTION("ReflectionQualityDescKey"));
			ReflectionQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
			ReflectionQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
			ReflectionQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
			ReflectionQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
			ReflectionQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			ReflectionQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetReflectionQuality));
			ReflectionQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetReflectionQuality));
			ReflectionQuality->SetShouldApplySettingsImmediately(true);
            
			ReflectionQuality->AddEditDependencyData(CreatedOverallQuality);
			CreatedOverallQuality->AddEditDependencyData(ReflectionQuality);
			GraphicsCategoryCollection->AddChildListData(ReflectionQuality);
		}

		// Post Processing Quality
		{
			UUI_ListDataObject_StringInteger* PostProcessingQuality = NewObject<UUI_ListDataObject_StringInteger>();
			PostProcessingQuality->SetDataID(FName(TEXT("PostProcessingQuality")));
			PostProcessingQuality->SetDataDisplayName(FText::FromString(TEXT("Post Processing Quality")));
			PostProcessingQuality->SetDescriptionRichText(GET_DESCRIPTION("PostProcessingQualityDescKey"));
			PostProcessingQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
			PostProcessingQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
			PostProcessingQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
			PostProcessingQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
			PostProcessingQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			PostProcessingQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetPostProcessingQuality));
			PostProcessingQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetPostProcessingQuality));
			PostProcessingQuality->SetShouldApplySettingsImmediately(true);
            
			PostProcessingQuality->AddEditDependencyData(CreatedOverallQuality);
			CreatedOverallQuality->AddEditDependencyData(PostProcessingQuality);
			GraphicsCategoryCollection->AddChildListData(PostProcessingQuality);
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
