// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "UITypes/UI_EnumTypes.h"
#include "UIWidget_ListEntry_Base.generated.h"

class UUI_ListDataObject_Base;
class UCommonTextBlock;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UUIWidget_ListEntry_Base : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On List Entry Widget Hovered"))
	void BP_OnListEntryWidgetHovered(const bool bWasHovered, const bool bIsEntryWidgetStillSelected);
	void NativeOnListEntryWidgetHovered(const bool bWasHovered);
	
protected:

	/** IUserObjectListEntry Interface */
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual void NativeOnEntryReleased() override;
	/** end IUserObjectListEntry Interface */

	/** UUserWidget Parent */
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
	/** end UUserWidget Parent */

	/** The child widget blueprint should override this function for the gamepad interaction to function properly */
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Get Widget To Focus For Gamepad"))
	UWidget* BP_GetWidgetToFocusForGamepad() const;
	
	/** The child class should override this function to handle the initialization needed. Super call is expected */
	virtual void OnOwningListDataObjectSet(UUI_ListDataObject_Base* InOwningListDataObject);

	/**
	 * The child class should override this function to update the UI values after the data object has been modified.
	 * Super call not needed.
	 */
	virtual void OnOwningListDataObjectModified(UUI_ListDataObject_Base* OwningModifiedData, EOptionsListDataModifyReason ModifyReason);
	virtual void OnOwningDependencyDataObjectModified(UUI_ListDataObject_Base* OwningModifiedDependencyData, EOptionsListDataModifyReason ModifyReason);

	/** The child class should override this to change the Editable State of the Widgets it owns. Super call is expected */
	virtual void OnToggleEditableState(bool bIsEditable);

	void SelectThisEntryWidget() const;

private:

	UPROPERTY(Transient)
	TObjectPtr<UUI_ListDataObject_Base> CachedOwningDataObject;

	/** Bound Widgets */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, AllowPrivateAccess = "true"))
	TObjectPtr<UCommonTextBlock> CommonText_SettingDisplayName;
	/** Bound Widgets */
};
