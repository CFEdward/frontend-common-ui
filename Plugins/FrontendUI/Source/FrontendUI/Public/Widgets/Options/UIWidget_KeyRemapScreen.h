// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonInputTypeEnum.h"
#include "Widgets/UIWidget_ActivatableBase.h"
#include "UIWidget_KeyRemapScreen.generated.h"

class UCommonRichTextBlock;
class FKeyRemapScreenInputPreprocessor;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UUIWidget_KeyRemapScreen : public UUIWidget_ActivatableBase
{
	GENERATED_BODY()
	
public:
	
	DECLARE_DELEGATE_OneParam(FOnKeyRemapScreenKeyPressedDelegate, const FKey& /*PressedKey*/);
	FOnKeyRemapScreenKeyPressedDelegate OnKeyRemapScreenKeyPressed;
	
	DECLARE_DELEGATE_OneParam(FOnKeyRemapScreenKeySelectCancelledDelegate, const FString& /*CancelReason*/);
	FOnKeyRemapScreenKeySelectCancelledDelegate OnKeyRemapScreenKeySelectCancelled;
	
	FORCEINLINE void SetDesiredInputTypeToFilter(const ECommonInputType InDesiredInputType) { CachedDesiredInputType = InDesiredInputType; }
	
protected:
	
	/** UCommonActivatableWidget Parent */
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
	/** end UCommonActivatableWidget Parent */
	
private:
	
	void OnValidKeyPressedDetected(const FKey& PressedKey);
	void OnKeySelectCancelled(const FString& CancelReason);
	
	/** Delay a tick to make sure the input key is captured properly before calling the PreDeactivateCallback and deactivating the widget */
	void RequestDeactivateWidget(TFunction<void()> PreDeactivateCallback);
	
	TSharedPtr<FKeyRemapScreenInputPreprocessor> CachedInputPreprocessor;
	ECommonInputType CachedDesiredInputType;
	
	/** Bound Widgets */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonRichTextBlock> CommonRichText_RemapMessage;
	/** Bound Widgets */
};