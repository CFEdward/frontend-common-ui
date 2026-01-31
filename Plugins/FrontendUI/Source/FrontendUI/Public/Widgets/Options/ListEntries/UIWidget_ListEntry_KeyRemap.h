// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UIWidget_ListEntry_Base.h"
#include "UIWidget_ListEntry_KeyRemap.generated.h"

class UUI_ListDataObject_KeyRemap;
class UUI_CommonButtonBase;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UUIWidget_ListEntry_KeyRemap : public UUIWidget_ListEntry_Base
{
	GENERATED_BODY()
	
protected:
	
	/** UUserWidget Parent */
	virtual void NativeOnInitialized() override;
	/** end UUserWidget Parent */
	
	/** UUIWidget_ListEntry_Base Parent */
	virtual void OnOwningListDataObjectSet(UUI_ListDataObject_Base* InOwningListDataObject) override;
	virtual void OnOwningListDataObjectModified(UUI_ListDataObject_Base* OwningModifiedData, EOptionsListDataModifyReason ModifyReason) override;
	/** end UUIWidget_ListEntry_Base Parent */
	
private:
	
	void OnRemapKeyButtonClicked();
	void ResetKeyBindingButtonClicked();
	
	UPROPERTY(Transient)
	TObjectPtr<UUI_ListDataObject_KeyRemap> CachedOwningKeyRemapDataObject;
	
	/** Bound Widgets */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UUI_CommonButtonBase> CommonButton_RemapKey;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UUI_CommonButtonBase> CommonButton_ResetKeyBinding;
	/** Bound Widgets */
};
