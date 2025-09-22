// Eduard Ciofu All Rights Reserved


#include "Widgets/Options/ListEntries/UIWidget_ListEntry_Base.h"

#include "CommonInputSubsystem.h"
#include "CommonTextBlock.h"
#include "Components/ListView.h"
#include "Widgets/Options/DataObjects/UI_ListDataObject_Base.h"

void UUIWidget_ListEntry_Base::NativeOnListEntryWidgetHovered(const bool bWasHovered)
{
	BP_OnListEntryWidgetHovered(bWasHovered, IsListItemSelected());
}

void UUIWidget_ListEntry_Base::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	OnOwningListDataObjectSet(CastChecked<UUI_ListDataObject_Base>(ListItemObject));
}

void UUIWidget_ListEntry_Base::NativeOnEntryReleased()
{
	IUserObjectListEntry::NativeOnEntryReleased();

	NativeOnListEntryWidgetHovered(false);
}

FReply UUIWidget_ListEntry_Base::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	const UCommonInputSubsystem* CommonInputSubsystem = GetInputSubsystem();
	if (IsValid(CommonInputSubsystem) && CommonInputSubsystem->GetCurrentInputType() == ECommonInputType::Gamepad)
	{
		if (const UWidget* WidgetToFocus = BP_GetWidgetToFocusForGamepad())
		{
			if (const TSharedPtr<SWidget> SlateWidgetToFocus = WidgetToFocus->GetCachedWidget())
			{
				return FReply::Handled().SetUserFocus(SlateWidgetToFocus.ToSharedRef());
			}
		}
	}

	return Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
}

void UUIWidget_ListEntry_Base::OnOwningListDataObjectSet(UUI_ListDataObject_Base* InOwningListDataObject)
{
	if (CommonText_SettingDisplayName)
	{
		CommonText_SettingDisplayName->SetText(InOwningListDataObject->GetDataDisplayName());
	}

	if (!InOwningListDataObject->OnListDataModified.IsBoundToObject(this))
	{
		InOwningListDataObject->OnListDataModified.AddUObject(this, &ThisClass::OnOwningListDataObjectModified);
	}

	if (!InOwningListDataObject->OnDependencyDataModified.IsBoundToObject(this))
	{
		InOwningListDataObject->OnDependencyDataModified.AddUObject(this, &ThisClass::OnOwningDependencyDataObjectModified);
	}
	
	OnToggleEditableState(InOwningListDataObject->IsDataCurrentlyEditable());
	CachedOwningDataObject = InOwningListDataObject;
}

void UUIWidget_ListEntry_Base::OnOwningListDataObjectModified(UUI_ListDataObject_Base* OwningModifiedData, EOptionsListDataModifyReason ModifyReason)
{
}

void UUIWidget_ListEntry_Base::OnOwningDependencyDataObjectModified(UUI_ListDataObject_Base* OwningModifiedDependencyData, EOptionsListDataModifyReason ModifyReason)
{
	if (IsValid(CachedOwningDataObject))
	{
		OnToggleEditableState(CachedOwningDataObject->IsDataCurrentlyEditable());
	}
}

void UUIWidget_ListEntry_Base::OnToggleEditableState(const bool bIsEditable)
{
	if (CommonText_SettingDisplayName)
	{
		CommonText_SettingDisplayName->SetIsEnabled(bIsEditable);
	}
}

void UUIWidget_ListEntry_Base::SelectThisEntryWidget() const
{
	CastChecked<UListView>(GetOwningListView())->SetSelectedItem(GetListItem());
}
