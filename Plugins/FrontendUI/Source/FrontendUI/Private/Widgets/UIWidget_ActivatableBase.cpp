// Eduard Ciofu All Rights Reserved


#include "Widgets/UIWidget_ActivatableBase.h"

#include "Controllers/UI_PlayerController.h"

AUI_PlayerController* UUIWidget_ActivatableBase::GetOwningUIPlayerController()
{
	if (!CachedOwningUIPC.IsValid())
	{
		CachedOwningUIPC = GetOwningPlayer<AUI_PlayerController>();
	}

	return CachedOwningUIPC.IsValid() ? CachedOwningUIPC.Get() : nullptr;
}
