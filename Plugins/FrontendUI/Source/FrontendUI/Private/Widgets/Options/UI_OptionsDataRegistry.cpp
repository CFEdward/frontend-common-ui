// Eduard Ciofu All Rights Reserved


#include "Widgets/Options/UI_OptionsDataRegistry.h"

#include "UI_BlueprintLibrary.h"
#include "UI_GameplayTags.h"
#include "UISettings/UI_GameUserSettings.h"
#include "Widgets/Options/UI_OptionsDataInteractionHelper.h"
#include "Widgets/Options/DataObjects/UI_ListDataObject_Collection.h"
#include "Widgets/Options/DataObjects/UI_ListDataObject_Scalar.h"
#include "Widgets/Options/DataObjects/UI_ListDataObject_String.h"

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
			OverallVolume->SetShouldApplySettingsImmediately(true);

			VolumeCategoryCollection->AddChildListData(OverallVolume);
		}
	}
	
	RegisteredOptionsTabCollections.Add(AudioTabCollection);
}

void UUI_OptionsDataRegistry::InitVideoCollectionTab()
{
	UUI_ListDataObject_Collection* VideoTabCollection = NewObject<UUI_ListDataObject_Collection>();
	VideoTabCollection->SetDataID(FName(TEXT("VideoTabCollection")));
	VideoTabCollection->SetDataDisplayName(FText::FromString(TEXT("Video")));

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
