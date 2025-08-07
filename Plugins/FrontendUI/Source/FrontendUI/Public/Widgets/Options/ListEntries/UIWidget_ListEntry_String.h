// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UIWidget_ListEntry_Base.h"
#include "UIWidget_ListEntry_String.generated.h"

class UUI_ListDataObject_String;
class UUI_CommonRotator;
class UUI_CommonButtonBase;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UUIWidget_ListEntry_String : public UUIWidget_ListEntry_Base
{
	GENERATED_BODY()
	
protected:

	/** UUserWidget Parent */
	virtual void NativeOnInitialized() override;
	/** end UUserWidget Parent */
	
	/** UUIWidget_ListEntry_Base Parent */
	virtual void OnOwningListDataObjectSet(UUI_ListDataObject_Base* InOwningListDataObject) override;
	/** end UUIWidget_ListEntry_Base Parent */
	
private:

	void OnPreviousOptionButtonClicked() const;
	void OnNextOptionButtonClicked() const;

	UPROPERTY(Transient)
	TObjectPtr<UUI_ListDataObject_String> CachedOwningStringDataObject;
	
	/*************** Bound Widgets ***************/
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UUI_CommonButtonBase> CommonButton_PreviousOption;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UUI_CommonRotator> CommonRotator_AvailableOptions;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UUI_CommonButtonBase> CommonButton_NextOption;
	/*************** Bound Widgets ***************/
};
