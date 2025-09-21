// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UI_ListDataObject_String.h"
#include "UI_ListDataObject_StringResolution.generated.h"

UCLASS()
class FRONTENDUI_API UUI_ListDataObject_StringResolution : public UUI_ListDataObject_String
{
	GENERATED_BODY()

public:

	void InitResolutionValues();

protected:

	/** UUI_ListDataObject_String Parent */
	virtual void OnDataObjectInitialized() override;
	/** end UUI_ListDataObject_String Parent */

private:

	FString ResToValueString(const FIntPoint& InResolution) const;
	FText ResToDisplayText(const FIntPoint& InResolution) const;

	FString MaximumAllowedResolution;
};
