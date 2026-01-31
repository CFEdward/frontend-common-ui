// Eduard Ciofu All Rights Reserved


#include "Widgets/Options/ListEntries/UIWidget_ListEntry_KeyRemap.h"

#include "UI_DebugHelper.h"
#include "Widgets/Components/UI_CommonButtonBase.h"
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
	Debug::Print(TEXT("Remap Key Button Clicked"));
}

void UUIWidget_ListEntry_KeyRemap::ResetKeyBindingButtonClicked()
{
	Debug::Print(TEXT("Reset Key Binding Button Clicked"));
}
