// Eduard Ciofu All Rights Reserved


#include "Widgets/Options/UIWidget_KeyRemapScreen.h"

void UUIWidget_KeyRemapScreen::NativeOnActivated()
{
	Super::NativeOnActivated();
	
	CachedInputPreprocessor = MakeShared<FKeyRemapScreenInputPreprocessor>(CachedDesiredInputType);
	
	FSlateApplication::Get().RegisterInputPreProcessor(CachedInputPreprocessor, -1);
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

void UUIWidget_KeyRemapScreen::SetDesiredInputTypeToFilter(const ECommonInputType InDesiredInputType)
{
	CachedDesiredInputType = InDesiredInputType;
}