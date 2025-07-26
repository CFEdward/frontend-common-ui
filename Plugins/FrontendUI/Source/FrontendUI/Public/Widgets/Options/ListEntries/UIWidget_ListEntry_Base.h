// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "UIWidget_ListEntry_Base.generated.h"

class UUI_ListDataObject_Base;
class UCommonTextBlock;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UUIWidget_ListEntry_Base : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:

	/** IUserObjectListEntry Interface */
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	/** end IUserObjectListEntry Interface */

	/** The child class should override this function to handle the initialization needed. Super call is expected */
	virtual void OnOwningListDataObjectSet(UUI_ListDataObject_Base* InOwningListDataObject);

private:

	/*************** Bound Widgets ***************/
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, AllowPrivateAccess = "true"))
	TObjectPtr<UCommonTextBlock> CommonText_SettingDisplayName;
	/*************** Bound Widgets ***************/
};
