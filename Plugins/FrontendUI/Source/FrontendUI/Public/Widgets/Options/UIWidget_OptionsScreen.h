// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widgets/UIWidget_ActivatableBase.h"
#include "UIWidget_OptionsScreen.generated.h"

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UUIWidget_OptionsScreen : public UUIWidget_ActivatableBase
{
	GENERATED_BODY()

protected:
	
	/** UUserWidget Parent */
	virtual void NativeOnInitialized() override;
	/** end UUserWidget Parent */

private:
	
	void OnResetBoundActionTriggered();
	void OnBackBoundActionTriggered();
	
	UPROPERTY(EditDefaultsOnly, Category = "Frontend Options Screen", meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle ResetAction;

	FUIActionBindingHandle ResetActionHandle;
};
