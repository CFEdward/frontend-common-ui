// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "UIWidget_ActivatableBase.generated.h"

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UUIWidget_ActivatableBase : public UCommonActivatableWidget
{
	GENERATED_BODY()
};
