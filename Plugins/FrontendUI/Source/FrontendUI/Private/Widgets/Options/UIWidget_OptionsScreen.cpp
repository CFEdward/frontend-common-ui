// Eduard Ciofu All Rights Reserved


#include "Widgets/Options/UIWidget_OptionsScreen.h"

#include "ICommonInputModule.h"
#include "UI_DebugHelper.h"
#include "Input/CommonUIInputTypes.h"

void UUIWidget_OptionsScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (!ResetAction.IsNull())
	{
		ResetActionHandle = RegisterUIActionBinding(
			FBindUIActionArgs(
				ResetAction,
				true,
				FSimpleDelegate::CreateUObject(this, &ThisClass::OnResetBoundActionTriggered)
			)
		);
	}

	RegisterUIActionBinding(
		FBindUIActionArgs(
			ICommonInputModule::GetSettings().GetDefaultBackAction(),
			true,
			FSimpleDelegate::CreateUObject(this, &ThisClass::OnBackBoundActionTriggered)
		)
	);
}

void UUIWidget_OptionsScreen::OnResetBoundActionTriggered()
{
	Debug::Print(TEXT("Reset bound action triggered"));
}

void UUIWidget_OptionsScreen::OnBackBoundActionTriggered()
{
	DeactivateWidget();
}
