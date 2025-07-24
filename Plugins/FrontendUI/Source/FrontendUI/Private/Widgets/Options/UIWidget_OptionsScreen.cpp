// Eduard Ciofu All Rights Reserved


#include "Widgets/Options/UIWidget_OptionsScreen.h"

#include "ICommonInputModule.h"
#include "UI_DebugHelper.h"
#include "Input/CommonUIInputTypes.h"
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

UUI_OptionsDataRegistry* UUIWidget_OptionsScreen::GetOrCreateDataRegistry()
{
	if (!CreatedOwningDataRegistry)
	{
		CreatedOwningDataRegistry = NewObject<UUI_OptionsDataRegistry>();
		CreatedOwningDataRegistry->InitOptionsDataRegistry(GetOwningLocalPlayer());
	}
	checkf(CreatedOwningDataRegistry, TEXT("Data reigstry for options screen is not valid"));

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

void UUIWidget_OptionsScreen::OnOptionsTabSelected(FName TabId)
{
	Debug::Print(TEXT("New Tab Selected. Tab ID: ") + TabId.ToString());
}
