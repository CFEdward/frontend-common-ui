// Eduard Ciofu All Rights Reserved


#include "Widgets/Options/UIWidget_OptionsScreen.h"

#include "ICommonInputModule.h"
#include "UI_DebugHelper.h"
#include "Input/CommonUIInputTypes.h"
#include "Subsystems/UI_Subsystem.h"
#include "UISettings/UI_GameUserSettings.h"
#include "Widgets/Components/UI_CommonButtonBase.h"
#include "Widgets/Components/UI_CommonListView.h"
#include "Widgets/Components/UI_TabListWidgetBase.h"
#include "Widgets/Options/UIWidget_OptionsDetailsView.h"
#include "Widgets/Options/UI_OptionsDataRegistry.h"
#include "Widgets/Options/DataObjects/UI_ListDataObject_Collection.h"
#include "Widgets/Options/ListEntries/UIWidget_ListEntry_Base.h"

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
	if (ResettableDataArray.IsEmpty()) return;

	UCommonButtonBase* SelectedTabButton = TabListWidget_OptionsTabs->GetTabButtonBaseByID(TabListWidget_OptionsTabs->GetActiveTab());
	const FString SelectedTabButtonName = CastChecked<UUI_CommonButtonBase>(SelectedTabButton)->GetButtonDisplayText().ToString();
	
	UUI_Subsystem::Get(this)->PushConfirmScreenToModalStackAsync(
		EConfirmScreenType::YesNo,
		FText::FromString(TEXT("Reset")),
		FText::FromString(TEXT("Are you sure you want to reset all the settings under the ") + SelectedTabButtonName + TEXT(" tab.")),
		[](EConfirmScreenButtonType ClickedButtonType)
			{
				
			}
	);
}

void UUIWidget_OptionsScreen::OnBackBoundActionTriggered()
{
	DeactivateWidget();
}

void UUIWidget_OptionsScreen::OnOptionsTabSelected(const FName TabId)
{
	DetailsView_ListEntryInfo->ClearDetailsViewInfo();
	
	const TArray<UUI_ListDataObject_Base*> FoundListSourceItems = GetOrCreateDataRegistry()->GetListSourceItemsBySelectedTabID(TabId);
	CommonListView_OptionsList->SetListItems(FoundListSourceItems);
	CommonListView_OptionsList->RequestRefresh();

	if (CommonListView_OptionsList->GetNumItems() != 0)
	{
		CommonListView_OptionsList->NavigateToIndex(0);
		CommonListView_OptionsList->SetSelectedIndex(0);
	}

	ResettableDataArray.Empty();
	for (UUI_ListDataObject_Base* FoundListSourceItem : FoundListSourceItems)
	{
		if (!IsValid(FoundListSourceItem)) continue;

		if (!FoundListSourceItem->OnListDataModified.IsBoundToObject(this))
		{
			FoundListSourceItem->OnListDataModified.AddUObject(this, &ThisClass::OnListViewListDataModified);
		}
		
		if (FoundListSourceItem->CanResetBackToDefaultValue())
		{
			ResettableDataArray.AddUnique(FoundListSourceItem);
		}
	}

	if (ResettableDataArray.IsEmpty())
	{
		RemoveActionBinding(ResetActionHandle);
	}
	else
	{
		if (!GetActionBindings().Contains(ResetActionHandle))
		{
			AddActionBinding(ResetActionHandle);
		}
	}
}

void UUIWidget_OptionsScreen::OnListViewItemHovered(UObject* InHoveredItem, const bool bWasHovered) const
{
	if (!IsValid(InHoveredItem)) return;

	UUIWidget_ListEntry_Base* HoveredEntryWidget = CommonListView_OptionsList->GetEntryWidgetFromItem<UUIWidget_ListEntry_Base>(InHoveredItem);
	check(HoveredEntryWidget);

	HoveredEntryWidget->NativeOnListEntryWidgetHovered(bWasHovered);

	if (bWasHovered)
	{
		DetailsView_ListEntryInfo->UpdateDetailsViewInfo(
			CastChecked<UUI_ListDataObject_Base>(InHoveredItem),
			TryGetEntryWidgetClassName(InHoveredItem)
		);
	}
	else
	{
		if (const UUI_ListDataObject_Base* SelectedItem = CommonListView_OptionsList->GetSelectedItem<UUI_ListDataObject_Base>())
		{
			DetailsView_ListEntryInfo->UpdateDetailsViewInfo(SelectedItem, TryGetEntryWidgetClassName(SelectedItem));
		}
	}
}

void UUIWidget_OptionsScreen::OnListViewItemSelected(UObject* InSelectedItem) const
{
	if (!IsValid(InSelectedItem)) return;

	DetailsView_ListEntryInfo->UpdateDetailsViewInfo(
		CastChecked<UUI_ListDataObject_Base>(InSelectedItem),
		TryGetEntryWidgetClassName(InSelectedItem)
	);
}

FString UUIWidget_OptionsScreen::TryGetEntryWidgetClassName(const UObject* InOwningListItem) const
{
	if (const UUserWidget* FoundEntryWidget = CommonListView_OptionsList->GetEntryWidgetFromItem(InOwningListItem))
	{
		return FoundEntryWidget->GetClass()->GetName();
	}

	return TEXT("Entry Widget Not Valid!");
}

void UUIWidget_OptionsScreen::OnListViewListDataModified(UUI_ListDataObject_Base* ModifiedData, EOptionsListDataModifyReason ModifyReason)
{
	if (!IsValid(ModifiedData)) return;

	if (ModifiedData->CanResetBackToDefaultValue())
	{
		ResettableDataArray.AddUnique(ModifiedData);

		if (!GetActionBindings().Contains(ResetActionHandle))
		{
			AddActionBinding(ResetActionHandle);
		}
	}
	else
	{
		if (ResettableDataArray.Contains(ModifiedData))
		{
			ResettableDataArray.Remove(ModifiedData);
		}
	}

	if (ResettableDataArray.IsEmpty())
	{
		RemoveActionBinding(ResetActionHandle);
	}
}
