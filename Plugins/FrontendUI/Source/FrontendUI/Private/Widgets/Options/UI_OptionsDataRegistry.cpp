﻿// Eduard Ciofu All Rights Reserved


#include "Widgets/Options/UI_OptionsDataRegistry.h"

#include "Widgets/Options/DataObjects/UI_ListDataObject_Collection.h"
#include "Widgets/Options/DataObjects/UI_ListDataObject_String.h"

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