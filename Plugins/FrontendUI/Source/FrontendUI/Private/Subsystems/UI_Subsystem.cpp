// Eduard Ciofu All Rights Reserved


#include "Subsystems/UI_Subsystem.h"

#include "UI_DebugHelper.h"
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

	Debug::Print(TEXT("Primary Layout widget stored"));
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
