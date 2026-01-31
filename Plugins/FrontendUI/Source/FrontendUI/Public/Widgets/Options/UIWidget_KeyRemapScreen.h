// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonInputTypeEnum.h"
#include "Framework/Application/IInputProcessor.h"
#include "Widgets/UIWidget_ActivatableBase.h"
#include "UIWidget_KeyRemapScreen.generated.h"

class UCommonRichTextBlock;

class FKeyRemapScreenInputPreprocessor : IInputProcessor
{
public:
	
	FKeyRemapScreenInputPreprocessor(const ECommonInputType InInputTypeToListenTo)
		: CachedInputTypeToListenTo(InInputTypeToListenTo)
	{
		
	}
	
	DECLARE_DELEGATE_OneParam(FOnInputPreProcessorKeyPressedDelegate, const FKey& /*PressedKey*/);
	FOnInputPreProcessorKeyPressedDelegate OnInputPreProcessorKeyPressed;
	
	DECLARE_DELEGATE_OneParam(FOnInputPreProcessorKeySelectCancelledDelegate, const FString& /*CancelReason*/);
	FOnInputPreProcessorKeySelectCancelledDelegate OnInputPreProcessorKeySelectCancelled;
	
protected:
	
	/** IInputProcessor Interface */
	virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override {}
	
	virtual bool HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override
	{
		ProcessPressedKey(InKeyEvent.GetKey());
		
		return true;
	}
	
	virtual bool HandleMouseButtonDownEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override
	{
		ProcessPressedKey(MouseEvent.GetEffectingButton());
		
		return true;
	}
	/** end IInputProcessor Interface */

private:
	
	void ProcessPressedKey(const FKey& InPressedKey) const
	{
		if (InPressedKey == EKeys::Escape)
		{
			OnInputPreProcessorKeySelectCancelled.ExecuteIfBound(TEXT("User cancelled Key Remap"));
			
			return;
		}
		
		switch (CachedInputTypeToListenTo)
		{
		case ECommonInputType::MouseAndKeyboard:
			if (InPressedKey.IsGamepadKey())
			{
				OnInputPreProcessorKeySelectCancelled.ExecuteIfBound(TEXT("Detected Gamepad Key pressed for keyboard inputs. Key Remap has been cancelled."));
				
				return;
			}
			
			break;
			
		case ECommonInputType::Gamepad:
			if (!InPressedKey.IsGamepadKey())
			{
				OnInputPreProcessorKeySelectCancelled.ExecuteIfBound(TEXT("Detected non-Gamepad Key pressed for Gamepad inputs. Key Remap has been cancelled."));
				
				return;
			}
				
			break;
			
		default:
			break;
		}
		
		OnInputPreProcessorKeyPressed.ExecuteIfBound(InPressedKey);
	}
	
	ECommonInputType CachedInputTypeToListenTo;
};

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UUIWidget_KeyRemapScreen : public UUIWidget_ActivatableBase
{
	GENERATED_BODY()
	
public:
	
	void SetDesiredInputTypeToFilter(const ECommonInputType InDesiredInputType);
	
protected:
	
	/** UCommonActivatableWidget Parent */
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
	/** end UCommonActivatableWidget Parent */
	
private:
	
	TSharedPtr<FKeyRemapScreenInputPreprocessor> CachedInputPreprocessor;
	ECommonInputType CachedDesiredInputType;
	
	/** Bound Widgets */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonRichTextBlock> CommonRichText_RemapMessage;
	/** Bound Widgets */
};