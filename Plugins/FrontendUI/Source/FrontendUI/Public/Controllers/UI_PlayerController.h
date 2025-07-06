// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UI_PlayerController.generated.h"

UCLASS()
class FRONTENDUI_API AUI_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	//~ Begin APlayerController Interface
	virtual void OnPossess(APawn* aPawn) override;
	//~ End APlayerController Interface
};
