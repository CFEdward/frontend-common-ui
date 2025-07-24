// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UI_OptionsDataRegistry.generated.h"

class UUI_ListDataObject_Collection;

UCLASS()
class FRONTENDUI_API UUI_OptionsDataRegistry : public UObject
{
	GENERATED_BODY()

public:

	/** Gets called by options screen right after the object UUI_OptionsDataRegistry is created */
	void InitOptionsDataRegistry(ULocalPlayer* InOwningLocalPlayer);

	const TArray<UUI_ListDataObject_Collection*>& GetRegisteredOptionsTabCollections() const { return RegisteredOptionsTabCollections; }

private:

	void InitGameplayCollectionTab();
	void InitAudioCollectionTab();
	void InitVideoCollectionTab();
	void InitControlCollectionTab();

	UPROPERTY(Transient)
	TArray<TObjectPtr<UUI_ListDataObject_Collection>> RegisteredOptionsTabCollections;
};
