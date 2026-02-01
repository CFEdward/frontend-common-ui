// Eduard Ciofu All Rights Reserved


#include "Widgets/Options/ListEntries/UIWidget_ListEntry_KeyRemap.h"

#include "UI_BlueprintLibrary.h"
#include "UI_DebugHelper.h"
#include "UI_GameplayTags.h"
#include "Subsystems/UI_Subsystem.h"
#include "Widgets/UIWidget_ActivatableBase.h"
#include "Widgets/Components/UI_CommonButtonBase.h"
#include "Widgets/Options/UIWidget_KeyRemapScreen.h"
#include "Widgets/Options/DataObjects/UI_ListDataObject_KeyRemap.h"

void UUIWidget_ListEntry_KeyRemap::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	CommonButton_RemapKey->OnClicked().AddUObject(this, &ThisClass::OnRemapKeyButtonClicked);
	CommonButton_ResetKeyBinding->OnClicked().AddUObject(this, &ThisClass::ResetKeyBindingButtonClicked);
}

void UUIWidget_ListEntry_KeyRemap::OnOwningListDataObjectSet(UUI_ListDataObject_Base* InOwningListDataObject)
{
	Super::OnOwningListDataObjectSet(InOwningListDataObject);
	
	CachedOwningKeyRemapDataObject = CastChecked<UUI_ListDataObject_KeyRemap>(InOwningListDataObject);
	
	CommonButton_RemapKey->SetButtonDisplayImage(CachedOwningKeyRemapDataObject->GetIconFromCurrentKey());
}

void UUIWidget_ListEntry_KeyRemap::OnOwningListDataObjectModified(UUI_ListDataObject_Base* OwningModifiedData, EOptionsListDataModifyReason ModifyReason)
{
	if (CachedOwningKeyRemapDataObject)
	{
		CommonButton_RemapKey->SetButtonDisplayImage(CachedOwningKeyRemapDataObject->GetIconFromCurrentKey());
	}
}

void UUIWidget_ListEntry_KeyRemap::OnRemapKeyButtonClicked()
{
	SelectThisEntryWidget();
	
	UUI_Subsystem::Get(this)->PushSoftWidgetToStackAsync(
		Frontend::WidgetStack::Modal,
		UUI_BlueprintLibrary::GetFrontendSoftWidgetClassByTag(Frontend::Widget::KeyRemapScreen),
		[this](const EAsyncPushWidgetState PushState, UUIWidget_ActivatableBase* PushedWidget)
		{
			if (PushState == EAsyncPushWidgetState::OnCreatedBeforePush)
			{
				UUIWidget_KeyRemapScreen* CreatedKeyRemapScreen = CastChecked<UUIWidget_KeyRemapScreen>(PushedWidget);
				CreatedKeyRemapScreen->OnKeyRemapScreenKeyPressed.BindUObject(this, &ThisClass::OnKeyToRemapPressed);
				CreatedKeyRemapScreen->OnKeyRemapScreenKeySelectCancelled.BindUObject(this, &ThisClass::OnKeyRemapCancelled);
				
				if (CachedOwningKeyRemapDataObject)
				{
					CreatedKeyRemapScreen->SetDesiredInputTypeToFilter(CachedOwningKeyRemapDataObject->GetDesiredInputKeyType());
				}
			}
		}
	);
}

void UUIWidget_ListEntry_KeyRemap::ResetKeyBindingButtonClicked()
{
	SelectThisEntryWidget();
	
	// Check if the current key is already the default key. Display an OK screen that says this is already the default key
	
	// Reset the key binding back to default
}

void UUIWidget_ListEntry_KeyRemap::OnKeyToRemapPressed(const FKey& PressedKey)
{
	if (CachedOwningKeyRemapDataObject)
	{
		CachedOwningKeyRemapDataObject->BindNewInputKey(PressedKey);
	}
}

void UUIWidget_ListEntry_KeyRemap::OnKeyRemapCancelled(const FString& CancelReason)
{
	UUI_Subsystem::Get(this)->PushConfirmScreenToModalStackAsync(
		EConfirmScreenType::OK,
		FText::FromString(TEXT("Key Remap")),
		FText::FromString(CancelReason),
		[](EConfirmScreenButtonType ClickedButton){}
	);
}
