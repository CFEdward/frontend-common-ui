// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonRotator.h"
#include "UI_CommonRotator.generated.h"

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UUI_CommonRotator : public UCommonRotator
{
	GENERATED_BODY()

public:

	void SetSelectedOptionByText(const FText& InTextOption);
};
