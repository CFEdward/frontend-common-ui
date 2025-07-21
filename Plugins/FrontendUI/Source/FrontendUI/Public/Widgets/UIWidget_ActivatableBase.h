// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "UIWidget_ActivatableBase.generated.h"

class AUI_PlayerController;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UUIWidget_ActivatableBase : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintPure)
	AUI_PlayerController* GetOwningUIPlayerController();
	
private:

	TWeakObjectPtr<AUI_PlayerController> CachedOwningUIPC;
};
