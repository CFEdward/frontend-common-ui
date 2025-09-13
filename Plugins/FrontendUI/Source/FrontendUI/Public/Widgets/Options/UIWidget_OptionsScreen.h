// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widgets/UIWidget_ActivatableBase.h"
#include "UIWidget_OptionsScreen.generated.h"

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

	void OnListViewItemHovered(UObject* InHoveredItem, const bool bWasHovered);
	void OnListViewItemSelected(UObject* InSelectedItem);

	/*************** Bound Widgets ***************/
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUI_TabListWidgetBase> TabListWidget_OptionsTabs;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUI_CommonListView> CommonListView_OptionsList;
	/*************** Bound Widgets ***************/

	/** Handle the creation of data in the options screen. Direct access to this variable is forbidden */
	UPROPERTY(Transient)
	TObjectPtr<UUI_OptionsDataRegistry> CreatedOwningDataRegistry;
	
	UPROPERTY(EditDefaultsOnly, Category = "Frontend Options Screen", meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle ResetAction;

	FUIActionBindingHandle ResetActionHandle;
};
