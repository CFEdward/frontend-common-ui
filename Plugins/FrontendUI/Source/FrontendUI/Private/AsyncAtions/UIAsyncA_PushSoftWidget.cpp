// Eduard Ciofu All Rights Reserved


#include "AsyncAtions/UIAsyncA_PushSoftWidget.h"

UUIAsyncA_PushSoftWidget* UUIAsyncA_PushSoftWidget::PushSoftWidget(const UObject* WorldContextObject, APlayerController* OwningPlayerController, TSoftClassPtr<UUIWidget_ActivatableBase> InSoftWidgetClass, FGameplayTag InWidgetStackTag, bool bFocusOnNewlyPushedWidget)
{
	checkf(!InSoftWidgetClass.IsNull(), TEXT("PushSoftWidgetToStack was passed a null soft widget class"));
	if (GEngine)
	{
		if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			UUIAsyncA_PushSoftWidget* Node = NewObject<UUIAsyncA_PushSoftWidget>();
			Node->RegisterWithGameInstance(World);

			return Node;
		}
	}

	return nullptr;
}
