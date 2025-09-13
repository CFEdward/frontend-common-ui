// Eduard Ciofu All Rights Reserved


#include "Widgets/Options/UIWidget_OptionsScreen.h"

#include "ICommonInputModule.h"
#include "UI_DebugHelper.h"
#include "Input/CommonUIInputTypes.h"
#include "UISettings/UI_GameUserSettings.h"
#include "Widgets/Components/UI_CommonListView.h"
#include "Widgets/Components/UI_TabListWidgetBase.h"
#include "Widgets/Options/UI_OptionsDataRegistry.h"
#include "Widgets/Options/DataObjects/UI_ListDataObject_Collection.h"

void UUIWidget_OptionsScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (!ResetAction.IsNull())
	{
		ResetActionHandle = RegisterUIActionBinding(
			FBindUIActionArgs(
				ResetAction,
				true,
				FSimpleDelegate::CreateUObject(this, &ThisClass::OnResetBoundActionTriggered)
			)
		);
	}

	RegisterUIActionBinding(
		FBindUIActionArgs(
			ICommonInputModule::GetSettings().GetDefaultBackAction(),
			true,
			FSimpleDelegate::CreateUObject(this, &ThisClass::OnBackBoundActionTriggered)
		)
	);

	TabListWidget_OptionsTabs->OnTabSelected.AddUniqueDynamic(this, &ThisClass::OnOptionsTabSelected);

	CommonListView_OptionsList->OnItemIsHoveredChanged().AddUObject(this, &ThisClass::OnListViewItemHovered);
	CommonListView_OptionsList->OnItemSelectionChanged().AddUObject(this, &ThisClass::OnListViewItemSelected);
}

void UUIWidget_OptionsScreen::NativeOnActivated()
{
	Super::NativeOnActivated();

	for (const UUI_ListDataObject_Collection* TabCollection : GetOrCreateDataRegistry()->GetRegisteredOptionsTabCollections())
	{
		if (!TabCollection)
		{
			continue;
		}

		const FName TabID = TabCollection->GetDataID();
		if (TabListWidget_OptionsTabs->GetTabButtonBaseByID(TabID) != nullptr)
		{
			continue;
		}

		TabListWidget_OptionsTabs->RequestRegisterTab(TabID, TabCollection->GetDataDisplayName());
	}
}

void UUIWidget_OptionsScreen::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();

	UUI_GameUserSettings::Get()->ApplySettings(true);
}

UUI_OptionsDataRegistry* UUIWidget_OptionsScreen::GetOrCreateDataRegistry()
{
	if (!CreatedOwningDataRegistry)
	{
		CreatedOwningDataRegistry = NewObject<UUI_OptionsDataRegistry>();
		CreatedOwningDataRegistry->InitOptionsDataRegistry(GetOwningLocalPlayer());
	}
	checkf(CreatedOwningDataRegistry, TEXT("Data registry for options screen is not valid"));

	return CreatedOwningDataRegistry;
}

void UUIWidget_OptionsScreen::OnResetBoundActionTriggered()
{
	Debug::Print(TEXT("Reset bound action triggered"));
}

void UUIWidget_OptionsScreen::OnBackBoundActionTriggered()
{
	DeactivateWidget();
}

void UUIWidget_OptionsScreen::OnOptionsTabSelected(const FName TabId)
{
	const TArray<UUI_ListDataObject_Base*> FoundListSourceItems = GetOrCreateDataRegistry()->GetListSourceItemsBySelectedTabID(TabId);
	CommonListView_OptionsList->SetListItems(FoundListSourceItems);

	if (CommonListView_OptionsList->GetNumItems() != 0)
	{
		CommonListView_OptionsList->NavigateToIndex(0);
		CommonListView_OptionsList->SetSelectedIndex(0);
	}
}

void UUIWidget_OptionsScreen::OnListViewItemHovered(UObject* InHoveredItem, bool bWasHovered)
{
	if (!InHoveredItem) return;

	const FString DebugString = CastChecked<UUI_ListDataObject_Base>(InHoveredItem)->GetDataDisplayName().ToString() +
		TEXT(" was ") +
		(bWasHovered ? TEXT("hovered") : TEXT("unhovered"));
	Debug::Print(DebugString);
}

void UUIWidget_OptionsScreen::OnListViewItemSelected(UObject* InSelectedItem)
{
	if (!InSelectedItem) return;

	const FString DebugString = CastChecked<UUI_ListDataObject_Base>(InSelectedItem)->GetDataDisplayName().ToString() +
		TEXT(" was selected");
	Debug::Print(DebugString);
}
