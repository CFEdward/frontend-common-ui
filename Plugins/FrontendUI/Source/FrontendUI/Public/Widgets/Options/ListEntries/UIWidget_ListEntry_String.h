// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UIWidget_ListEntry_Base.h"
#include "UIWidget_ListEntry_String.generated.h"

class UUI_CommonRotator;
class UUI_CommonButtonBase;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UUIWidget_ListEntry_String : public UUIWidget_ListEntry_Base
{
	GENERATED_BODY()

private:

	/*************** Bound Widgets ***************/
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UUI_CommonButtonBase> CommonButton_Decrease;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UUI_CommonRotator> CommonRotator_AvailableOptions;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UUI_CommonButtonBase> CommonButton_Increase;
	/*************** Bound Widgets ***************/
};
