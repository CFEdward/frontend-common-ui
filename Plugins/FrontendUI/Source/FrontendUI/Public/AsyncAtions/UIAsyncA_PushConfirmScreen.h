// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "UITypes/UI_EnumTypes.h"
#include "UIAsyncA_PushConfirmScreen.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConfirmScreenButtonClicked, EConfirmScreenButtonType, ClickedButtonType);

UCLASS()
class FRONTENDUI_API UUIAsyncA_PushConfirmScreen : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	/** UBlueprintAsyncActionBase Parent */
	virtual void Activate() override;
	/** end UBlueprintAsyncActionBase Parent */

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject", BlueprintInternalUseOnly = "true", DisplayName = "Show Confirmation Screen"))
	static UUIAsyncA_PushConfirmScreen* PushConfirmScreen(const UObject* WorldContextObject, EConfirmScreenType ScreenType, FText InScreenTitle, FText InScreenMessage);

	UPROPERTY(BlueprintAssignable)
	FOnConfirmScreenButtonClicked OnButtonClicked;
	
private:

	TWeakObjectPtr<UWorld> CachedOwningWorld;
	EConfirmScreenType CachedScreenType;
	FText CachedScreenTitle;
	FText CachedScreenMessage;
};
