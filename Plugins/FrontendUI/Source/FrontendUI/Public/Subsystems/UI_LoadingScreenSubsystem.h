// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UI_LoadingScreenSubsystem.generated.h"

UCLASS()
class FRONTENDUI_API UUI_LoadingScreenSubsystem : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()
	
public:
	
	/** USubsystem Parent */
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	/** end USubsystem Parent */
	
	/** FTickableGameObject Parent */
	virtual UWorld* GetTickableGameObjectWorld() const override;
	/** end FTickableGameObject Parent */
	
	/** FTickableObjectBase Parent */
	virtual void Tick(float DeltaTime) override;
	virtual ETickableTickType GetTickableTickType() const override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;
	/** end FTickableObjectBase Parent */
	
private:
	
	void OnMapPreLoaded(const FWorldContext& WorldContext, const FString& MapName);
	void OnMapPostLoaded(UWorld* LoadedWorld);
};
