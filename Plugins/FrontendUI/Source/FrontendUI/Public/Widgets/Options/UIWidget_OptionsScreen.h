// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UITypes/UIEnumTypes.h"
#include "Widgets/UIWidget_ActivatableBase.h"
#include "UIWidget_OptionsScreen.generated.h"

class UUI_ListDataObject_Base;
class UUIWidget_OptionsDetailsView;
class UUI_CommonListView;
class UUI_TabListWidgetBase;
class UUI_OptionsDataRegistry;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UUIWidget_OptionsScreen : public UUIWidget_ActivatableBase
{
	GENERATED_BODY()

protected:
	
	/** UUserWidget Parent */
	virtual void NativeOnInitialized() override;
	/** end UUserWidget Parent */

	/** UCommonActivatableWidget Parent */
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
	/** end UCommonActivatableWidget Parent */
	
private:

	UUI_OptionsDataRegistry* GetOrCreateDataRegistry();
	
	void OnResetBoundActionTriggered();
	void OnBackBoundActionTriggered();

	UFUNCTION()
	void OnOptionsTabSelected(FName TabId);

	void OnListViewItemHovered(UObject* InHoveredItem, const bool bWasHovered) const;
	void OnListViewItemSelected(UObject* InSelectedItem) const;

	FString TryGetEntryWidgetClassName(const UObject* InOwningListItem) const;

	void OnListViewListDataModified(UUI_ListDataObject_Base* ModifiedData, EOptionsListDataModifyReason ModifyReason);

	/*************** Bound Widgets ***************/
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUI_TabListWidgetBase> TabListWidget_OptionsTabs;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUI_CommonListView> CommonListView_OptionsList;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUIWidget_OptionsDetailsView> DetailsView_ListEntryInfo;
	/*************** Bound Widgets ***************/

	/** Handle the creation of data in the options screen. Direct access to this variable is forbidden */
	UPROPERTY(Transient)
	TObjectPtr<UUI_OptionsDataRegistry> CreatedOwningDataRegistry;
	
	UPROPERTY(EditDefaultsOnly, Category = "Frontend Options Screen", meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle ResetAction;

	FUIActionBindingHandle ResetActionHandle;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UUI_ListDataObject_Base>> ResettableDataArray;
};
