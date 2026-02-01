// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UI_LoadingScreenInterface.generated.h"

UINTERFACE(BlueprintType, MinimalAPI)
class UUI_LoadingScreenInterface : public UInterface
{
	GENERATED_BODY()
};

class FRONTENDUI_API IUI_LoadingScreenInterface
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent)
	void OnLoadingScreenActivated();
	
	UFUNCTION(BlueprintNativeEvent)
	void OnLoadingScreenDeactivated();
};
