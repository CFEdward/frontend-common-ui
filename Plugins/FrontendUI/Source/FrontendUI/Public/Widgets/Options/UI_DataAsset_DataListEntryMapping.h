// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UI_DataAsset_DataListEntryMapping.generated.h"

class UUIWidget_ListEntry_Base;
class UUI_ListDataObject_Base;

UCLASS()
class FRONTENDUI_API UUI_DataAsset_DataListEntryMapping : public UDataAsset
{
	GENERATED_BODY()

public:

	TSubclassOf<UUIWidget_ListEntry_Base> FindEntryWidgetClassByDataObject(const UUI_ListDataObject_Base* InDataObject) const;
	
private:

	UPROPERTY(EditDefaultsOnly)
	TMap<TSubclassOf<UUI_ListDataObject_Base>, TSubclassOf<UUIWidget_ListEntry_Base>> DataObjectListEntryMap;
};
