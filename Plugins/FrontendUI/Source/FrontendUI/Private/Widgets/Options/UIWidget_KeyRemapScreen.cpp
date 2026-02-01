// Eduard Ciofu All Rights Reserved


#include "Widgets/Options/UIWidget_KeyRemapScreen.h"

#include "CommonInputSubsystem.h"
#include "CommonRichTextBlock.h"
#include "CommonUITypes.h"
#include "ICommonInputModule.h"
#include "Framework/Application/IInputProcessor.h"

class FKeyRemapScreenInputPreprocessor : public IInputProcessor
{
public:
	
	FKeyRemapScreenInputPreprocessor(const ECommonInputType InInputTypeToListenTo, ULocalPlayer* InOwningLocalPlayer)
		: CachedInputTypeToListenTo(InInputTypeToListenTo), CachedWeakOwningLocalPlayer(InOwningLocalPlayer)
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
		
		UCommonInputSubsystem* CommonInputSubsystem = UCommonInputSubsystem::Get(CachedWeakOwningLocalPlayer.Get());
		check(CommonInputSubsystem);
		
		ECommonInputType CurrentInputType = CommonInputSubsystem->GetCurrentInputType();
		
		switch (CachedInputTypeToListenTo)
		{
		case ECommonInputType::MouseAndKeyboard:
			if (InPressedKey.IsGamepadKey() || CurrentInputType == ECommonInputType::Gamepad)
			{
				OnInputPreProcessorKeySelectCancelled.ExecuteIfBound(TEXT("Detected Gamepad Key pressed for keyboard inputs. Key Remap has been cancelled."));
				
				return;
			}
			break;
			
		case ECommonInputType::Gamepad:
			if (CurrentInputType == ECommonInputType::Gamepad && InPressedKey == EKeys::LeftMouseButton)
			{
				FCommonInputActionDataBase* InputActionData = ICommonInputModule::GetSettings().GetDefaultClickAction().GetRow<FCommonInputActionDataBase>(TEXT(""));
				check(InputActionData);
				
				OnInputPreProcessorKeyPressed.ExecuteIfBound(InputActionData->GetDefaultGamepadInputTypeInfo().GetKey());
				
				return;
			}
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
	TWeakObjectPtr<ULocalPlayer> CachedWeakOwningLocalPlayer;
};

void UUIWidget_KeyRemapScreen::NativeOnActivated()
{
	Super::NativeOnActivated();
	
	CachedInputPreprocessor = MakeShared<FKeyRemapScreenInputPreprocessor>(CachedDesiredInputType, GetOwningLocalPlayer());
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
