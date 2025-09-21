// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UITypes/UI_EnumTypes.h"
#include "UI_Subsystem.generated.h"

class UUI_CommonButtonBase;
class UUIWidget_ActivatableBase;
struct FGameplayTag;
class UUIWidget_PrimaryLayout;

enum class EAsyncPushWidgetState : uint8
{
	OnCreatedBeforePush,
	AfterPush
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonDescriptionTextUpdated, UUI_CommonButtonBase*, BroadcastingButton, FText, DescriptionText);

UCLASS()
class FRONTENDUI_API UUI_Subsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	/** USubsystem Parent */
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	/** end USubsystem Parent */

	UFUNCTION(BlueprintCallable)
	void RegisterCreatedPrimaryLayoutWidget(UUIWidget_PrimaryLayout* InCreatedWidget);

	void PushSoftWidgetToStackAsync(const FGameplayTag& InWidgetStackTag, TSoftClassPtr<UUIWidget_ActivatableBase> InSoftWidgetClass, TFunction<void(EAsyncPushWidgetState, UUIWidget_ActivatableBase*)> AsyncPushStateCallback) const;
	void PushConfirmScreenToModalStackAsync(EConfirmScreenType InScreenType, const FText& InScreenTitle, const FText& InScreenMsg, TFunction<void(EConfirmScreenButtonType)> ButtonClickedCallback) const;
	
	static UUI_Subsystem* Get(const UObject* WorldContextObject);

	UPROPERTY(BlueprintAssignable)
	FOnButtonDescriptionTextUpdated OnButtonDescriptionTextUpdated;

private:

	UPROPERTY(Transient)
	TObjectPtr<UUIWidget_PrimaryLayout> CreatedPrimaryLayout;
};
