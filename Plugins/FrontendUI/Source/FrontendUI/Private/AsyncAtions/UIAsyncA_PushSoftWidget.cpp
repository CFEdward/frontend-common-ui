// Eduard Ciofu All Rights Reserved


#include "AsyncAtions/UIAsyncA_PushSoftWidget.h"

#include "Subsystems/UI_Subsystem.h"
#include "Widgets/UIWidget_ActivatableBase.h"

void UUIAsyncA_PushSoftWidget::Activate()
{
	const UUI_Subsystem* UISubsystem = UUI_Subsystem::Get(CachedOwningWorld.Get());
	UISubsystem->PushSoftWidgetToStackAsync(
		CachedWidgetStackTag,
		CachedSoftWidgetClass,
		[this](const EAsyncPushWidgetState InPushState, UUIWidget_ActivatableBase* PushedWidget)
		{
			switch (InPushState)
			{
			case EAsyncPushWidgetState::OnCreatedBeforePush:
				PushedWidget->SetOwningPlayer(CachedOwningPC.Get());
				OnWidgetCreatedBeforePush.Broadcast(PushedWidget);
				break;
				
			case EAsyncPushWidgetState::AfterPush:
				AfterPush.Broadcast(PushedWidget);
				if (bCachedFocusOnNewlyPushedWidget)
				{
					if (UWidget* WidgetToFocus = PushedWidget->GetDesiredFocusTarget())
					{
						WidgetToFocus->SetFocus();
					}
				}

				SetReadyToDestroy();
				break;

			default:
				break;
			}
		}
	);
}

UUIAsyncA_PushSoftWidget* UUIAsyncA_PushSoftWidget::PushSoftWidget(const UObject* WorldContextObject, APlayerController* OwningPlayerController, const TSoftClassPtr<UUIWidget_ActivatableBase> InSoftWidgetClass, const FGameplayTag InWidgetStackTag, const bool bFocusOnNewlyPushedWidget)
{
	checkf(!InSoftWidgetClass.IsNull(), TEXT("PushSoftWidgetToStack was passed a null soft widget class"));
	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			UUIAsyncA_PushSoftWidget* Node = NewObject<UUIAsyncA_PushSoftWidget>();
			Node->CachedOwningWorld = World;
			Node->CachedOwningPC = OwningPlayerController;
			Node->CachedSoftWidgetClass = InSoftWidgetClass;
			Node->CachedWidgetStackTag = InWidgetStackTag;
			Node->bCachedFocusOnNewlyPushedWidget = bFocusOnNewlyPushedWidget;
			
			Node->RegisterWithGameInstance(World);

			return Node;
		}
	}

	return nullptr;
}
