// Eduard Ciofu All Rights Reserved


#include "Widgets/Options/UI_OptionsDataRegistry.h"

#include "UISettings/UI_GameUserSettings.h"
#include "Widgets/Options/UI_OptionsDataInteractionHelper.h"
#include "Widgets/Options/DataObjects/UI_ListDataObject_Collection.h"
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

	/*
	TSharedPtr<FUI_OptionsDataInteractionHelper> ConstructedHelper = MakeShared<FUI_OptionsDataInteractionHelper>(
		GET_FUNCTION_NAME_STRING_CHECKED(UUI_GameUserSettings, GetCurrentGameDifficulty)
	);
	*/
	
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
		TestItem->SetDataDisplayName(FText::FromString(TEXT("Test")));

		GameplayTabCollection->AddChildListData(TestItem);
	}

	RegisteredOptionsTabCollections.Add(GameplayTabCollection);
}

void UUI_OptionsDataRegistry::InitAudioCollectionTab()
{
	UUI_ListDataObject_Collection* AudioTabCollection = NewObject<UUI_ListDataObject_Collection>();
	AudioTabCollection->SetDataID(FName(TEXT("AudioTabCollection")));
	AudioTabCollection->SetDataDisplayName(FText::FromString(TEXT("Audio")));

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

	return FoundTabCollection->GetAllChildListData();
}