// Eduard Ciofu All Rights Reserved


#include "Subsystems/UI_LoadingScreenSubsystem.h"

#include "PreLoadScreenManager.h"

bool UUI_LoadingScreenSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance())
	{
		TArray<UClass*> FoundClasses;
		GetDerivedClasses(GetClass(), FoundClasses);

		return FoundClasses.IsEmpty();
	}
	
	return false;
}

void UUI_LoadingScreenSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	FCoreUObjectDelegates::PreLoadMapWithContext.AddUObject(this, &ThisClass::OnMapPreLoaded);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &ThisClass::OnMapPostLoaded);
}

void UUI_LoadingScreenSubsystem::Deinitialize()
{
	FCoreUObjectDelegates::PreLoadMapWithContext.RemoveAll(this);
	FCoreUObjectDelegates::PostLoadMapWithWorld.RemoveAll(this);
}

UWorld* UUI_LoadingScreenSubsystem::GetTickableGameObjectWorld() const
{
	if (const UGameInstance* OwningGameInstance = GetGameInstance())
	{
		return OwningGameInstance->GetWorld();
	}
	
	return nullptr;
}

void UUI_LoadingScreenSubsystem::Tick(float DeltaTime)
{
	TryUpdateLoadingScreen();
}

ETickableTickType UUI_LoadingScreenSubsystem::GetTickableTickType() const
{
	if (IsTemplate())
	{
		return ETickableTickType::Never;
	}
	
	return ETickableTickType::Conditional;
}

bool UUI_LoadingScreenSubsystem::IsTickable() const
{
	return GetGameInstance() && GetGameInstance()->GetGameViewportClient();
}

TStatId UUI_LoadingScreenSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UUI_LoadingScreenSubsystem, STATGROUP_Tickables);
}

void UUI_LoadingScreenSubsystem::OnMapPreLoaded(const FWorldContext& WorldContext, const FString& MapName)
{
	if (WorldContext.OwningGameInstance != GetGameInstance()) return;
	
	SetTickableTickType(ETickableTickType::Conditional);
	bIsCurrentlyLoadingMap = true;
	
	TryUpdateLoadingScreen();
}

void UUI_LoadingScreenSubsystem::OnMapPostLoaded(UWorld* LoadedWorld)
{
	if (LoadedWorld && LoadedWorld->GetGameInstance() == GetGameInstance())
	{
		bIsCurrentlyLoadingMap = false;
	}
}

void UUI_LoadingScreenSubsystem::TryUpdateLoadingScreen()
{
	// Check if there's any start up loading screen that's currently active
	if (IsPreLoadScreenActive()) return;
	
	// Check if we should show the loading screen
	if (true)
	{
		// Try to display the loading screen here
	}
	else
	{
		// Try to remove the current active loading screen
		
		// Notify the loading is complete
		
		// Disable the ticking
		SetTickableTickType(ETickableTickType::Never);
	}
}

bool UUI_LoadingScreenSubsystem::IsPreLoadScreenActive() const
{
	if (const FPreLoadScreenManager* PreLoadScreenManager = FPreLoadScreenManager::Get())
	{
		return PreLoadScreenManager->HasValidActivePreLoadScreen();
	}
	
	return false;
}
