// Eduard Ciofu All Rights Reserved


#include "AsyncAtions/UIAsyncA_PushConfirmScreen.h"

#include "Subsystems/UI_Subsystem.h"

void UUIAsyncA_PushConfirmScreen::Activate()
{
	UUI_Subsystem::Get(CachedOwningWorld.Get())->PushConfirmScreenToModalStackAsync(
		CachedScreenType,
		CachedScreenTitle,
		CachedScreenMessage,
		[this](const EConfirmScreenButtonType ClickedButtonType)
		{
			OnButtonClicked.Broadcast(ClickedButtonType);
			SetReadyToDestroy();
		}
	);
}

UUIAsyncA_PushConfirmScreen* UUIAsyncA_PushConfirmScreen::PushConfirmScreen(const UObject* WorldContextObject, const EConfirmScreenType ScreenType, const FText InScreenTitle, const FText InScreenMessage)
{
	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			UUIAsyncA_PushConfirmScreen* Node = NewObject<UUIAsyncA_PushConfirmScreen>();
			Node->CachedOwningWorld = World;
			Node->CachedScreenType = ScreenType;
			Node->CachedScreenTitle = InScreenTitle;
			Node->CachedScreenMessage = InScreenMessage;

			Node->RegisterWithGameInstance(World);

			return Node;
		}
	}

	return nullptr;
}
