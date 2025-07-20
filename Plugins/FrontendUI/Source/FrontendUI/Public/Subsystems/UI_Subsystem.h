// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UI_Subsystem.generated.h"

class UUIWidget_PrimaryLayout;

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
	
	static UUI_Subsystem* Get(const UObject* WorldContextObject);

private:

	UPROPERTY(Transient)
	TObjectPtr<UUIWidget_PrimaryLayout> CreatedPrimaryLayout;
};
