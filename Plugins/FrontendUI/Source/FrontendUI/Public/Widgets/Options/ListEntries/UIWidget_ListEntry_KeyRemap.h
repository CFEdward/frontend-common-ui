// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UIWidget_ListEntry_Base.h"
#include "UIWidget_ListEntry_KeyRemap.generated.h"

class UUI_CommonButtonBase;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UUIWidget_ListEntry_KeyRemap : public UUIWidget_ListEntry_Base
{
	GENERATED_BODY()
	
private:
	
	/** Bound Widgets */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UUI_CommonButtonBase> CommonButton_RemapKey;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UUI_CommonButtonBase> CommonButton_ResetKeyBinding;
	/** Bound Widgets */
};
