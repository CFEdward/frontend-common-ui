// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UI_Subsystem.generated.h"

class UUIWidget_ActivatableBase;
struct FGameplayTag;
class UUIWidget_PrimaryLayout;

enum class EAsyncPushWidgetState : uint8
{
	OnCreatedBeforePush,
	AfterPush
};

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
	
	static UUI_Subsystem* Get(const UObject* WorldContextObject);

private:

	UPROPERTY(Transient)
	TObjectPtr<UUIWidget_PrimaryLayout> CreatedPrimaryLayout;
};
