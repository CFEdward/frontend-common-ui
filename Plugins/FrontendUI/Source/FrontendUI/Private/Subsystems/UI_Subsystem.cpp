// Eduard Ciofu All Rights Reserved


#include "Subsystems/UI_Subsystem.h"

#include "UI_BlueprintLibrary.h"
#include "UI_DebugHelper.h"
#include "UI_GameplayTags.h"
#include "Engine/AssetManager.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "Widgets/UIWidget_ActivatableBase.h"
#include "Widgets/UIWidget_ConfirmScreen.h"
#include "Widgets/UIWidget_PrimaryLayout.h"

bool UUI_Subsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance())
	{
		TArray<UClass*> FoundClasses;
		GetDerivedClasses(GetClass(), FoundClasses);

		return FoundClasses.IsEmpty();
	}
	
	return false;
}

void UUI_Subsystem::RegisterCreatedPrimaryLayoutWidget(UUIWidget_PrimaryLayout* InCreatedWidget)
{
	check(InCreatedWidget);
	
	CreatedPrimaryLayout = InCreatedWidget;
}

void UUI_Subsystem::PushSoftWidgetToStackAsync(const FGameplayTag& InWidgetStackTag, TSoftClassPtr<UUIWidget_ActivatableBase> InSoftWidgetClass, TFunction<void(EAsyncPushWidgetState, UUIWidget_ActivatableBase*)> AsyncPushStateCallback) const
{
	check(!InSoftWidgetClass.IsNull());

	UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
		InSoftWidgetClass.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda([this, InSoftWidgetClass, InWidgetStackTag, AsyncPushStateCallback]()
			{
				UClass* LoadedWidgetClass = InSoftWidgetClass.Get();
				check(LoadedWidgetClass && CreatedPrimaryLayout);

				UCommonActivatableWidgetContainerBase* FoundWidgetStack = CreatedPrimaryLayout->FindWidgetStackByTag(InWidgetStackTag);
				UUIWidget_ActivatableBase* CreatedWidget = FoundWidgetStack->AddWidget<UUIWidget_ActivatableBase>(
					LoadedWidgetClass,
					[AsyncPushStateCallback](UUIWidget_ActivatableBase& CreatedWidgetInstance)
					{
						AsyncPushStateCallback(EAsyncPushWidgetState::OnCreatedBeforePush, &CreatedWidgetInstance);
					}
				);

				AsyncPushStateCallback(EAsyncPushWidgetState::AfterPush, CreatedWidget);
			}
		)
	);
}

void UUI_Subsystem::PushConfirmScreenToModalStackAsync(const EConfirmScreenType InScreenType, const FText& InScreenTitle, const FText& InScreenMsg, TFunction<void(EConfirmScreenButtonType)> ButtonClickedCallback) const
{
	UUI_ConfirmScreenInfoObject* CreatedInfoObject = nullptr;
	
	switch (InScreenType)
	{
	case EConfirmScreenType::OK:
		CreatedInfoObject = UUI_ConfirmScreenInfoObject::CreateOKScreen(InScreenTitle, InScreenMsg);
		break;

	case EConfirmScreenType::YesNo:
		CreatedInfoObject = UUI_ConfirmScreenInfoObject::CreateYesNoScreen(InScreenTitle, InScreenMsg);
		break;

	case EConfirmScreenType::OKCancel:
		CreatedInfoObject = UUI_ConfirmScreenInfoObject::CreateOKCancelScreen(InScreenTitle, InScreenMsg);
		break;

	case EConfirmScreenType::Unknown:
	default:
		break;
	}

	check(CreatedInfoObject);

	PushSoftWidgetToStackAsync(
		Frontend::WidgetStack::Modal,
		UUI_BlueprintLibrary::GetFrontendSoftWidgetClassByTag(Frontend::Widget::ConfirmScreen),
		[CreatedInfoObject, ButtonClickedCallback](const EAsyncPushWidgetState InPushState, UUIWidget_ActivatableBase* PushedWidget)
		{
			if (InPushState == EAsyncPushWidgetState::OnCreatedBeforePush)
			{
				UUIWidget_ConfirmScreen* CreatedConfirmScreen = CastChecked<UUIWidget_ConfirmScreen>(PushedWidget);
				CreatedConfirmScreen->InitConfirmScreen(CreatedInfoObject, ButtonClickedCallback);
			}
		}
	);
}

UUI_Subsystem* UUI_Subsystem::Get(const UObject* WorldContextObject)
{
	if (GEngine)
	{
		const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert);

		return UGameInstance::GetSubsystem<UUI_Subsystem>(World->GetGameInstance());
	}

	return nullptr;
}
