// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonInputTypeEnum.h"
#include "UI_DebugHelper.h"
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
	
protected:
	
	/** IInputProcessor Interface */
	virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override {}
	
	virtual bool HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override
	{
		Debug::Print(TEXT("Pressed Key: ") + InKeyEvent.GetKey().GetDisplayName().ToString());

		const UEnum* StaticCommonInputType = StaticEnum<ECommonInputType>();
		Debug::Print(TEXT("Desired Input Key Type: ") + StaticCommonInputType->GetValueAsString(CachedInputTypeToListenTo));
		
		return true;
	}
	
	virtual bool HandleMouseButtonDownEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override
	{
		Debug::Print(TEXT("Pressed Key: ") + MouseEvent.GetEffectingButton().GetDisplayName().ToString());
		
		return true;
	}
	/** end IInputProcessor Interface */
	
private:
	
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