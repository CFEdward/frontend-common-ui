// Eduard Ciofu All Rights Reserved


#include "Widgets/Options/UIWidget_KeyRemapScreen.h"

#include "CommonRichTextBlock.h"
#include "UI_DebugHelper.h"
#include "Framework/Application/IInputProcessor.h"

class FKeyRemapScreenInputPreprocessor : public IInputProcessor
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
			
		default: break;
		}
		
		OnInputPreProcessorKeyPressed.ExecuteIfBound(InPressedKey);
	}
	
	ECommonInputType CachedInputTypeToListenTo;
};

void UUIWidget_KeyRemapScreen::NativeOnActivated()
{
	Super::NativeOnActivated();
	
	CachedInputPreprocessor = MakeShared<FKeyRemapScreenInputPreprocessor>(CachedDesiredInputType);
	CachedInputPreprocessor->OnInputPreProcessorKeyPressed.BindUObject(this, &ThisClass::OnValidKeyPressedDetected);
	CachedInputPreprocessor->OnInputPreProcessorKeySelectCancelled.BindUObject(this, &ThisClass::OnKeySelectCancelled);
	
	FSlateApplication::Get().RegisterInputPreProcessor(CachedInputPreprocessor, -1);
	
	FString InputDeviceName;
	switch (CachedDesiredInputType)
	{
	case ECommonInputType::MouseAndKeyboard:
		InputDeviceName = TEXT("Mouse & Keyboard");
		break;
		
	case ECommonInputType::Gamepad:
		InputDeviceName = TEXT("Gamepad");
		break;

	default: break;
	}
	
	const FString DisplayRichMessage = FString::Printf(TEXT("<KeyRemapDefault>Press any </><KeyRemapHighlight>%s</><KeyRemapDefault> key.</>"), *InputDeviceName);
	CommonRichText_RemapMessage->SetText(FText::FromString(DisplayRichMessage));
}

void UUIWidget_KeyRemapScreen::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();
	
	if (CachedInputPreprocessor)
	{
		FSlateApplication::Get().UnregisterInputPreProcessor(CachedInputPreprocessor);
		
		CachedInputPreprocessor.Reset();
	}
}

void UUIWidget_KeyRemapScreen::OnValidKeyPressedDetected(const FKey& PressedKey)
{
	RequestDeactivateWidget([this, PressedKey]()
		{
			OnKeyRemapScreenKeyPressed.ExecuteIfBound(PressedKey);
		}
	);
}

void UUIWidget_KeyRemapScreen::OnKeySelectCancelled(const FString& CancelReason)
{
	RequestDeactivateWidget([this, CancelReason]()
		{
			OnKeyRemapScreenKeySelectCancelled.ExecuteIfBound(CancelReason);
		}
	);
}

void UUIWidget_KeyRemapScreen::RequestDeactivateWidget(TFunction<void()> PreDeactivateCallback)
{
	// Delay a tick to make sure the input is processed correctly
	FTSTicker::GetCoreTicker().AddTicker(
		FTickerDelegate::CreateLambda(
			[PreDeactivateCallback, this](float DeltaTime)->bool
			{
				PreDeactivateCallback();
				DeactivateWidget();
				
				return false;
			}
		)
	);
}
