// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "UI_CommonButtonBase.generated.h"

class UCommonTextBlock;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UUI_CommonButtonBase : public UCommonButtonBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void SetButtonText(FText InText) const;

protected:

	/** UUserWidget Parent */
	virtual void NativePreConstruct() override;
	/** end UUserWidget Parent */

	/** UCommonButtonBase Parent */
	virtual void NativeOnCurrentTextStyleChanged() override;
	virtual void NativeOnHovered() override;
	virtual void NativeOnUnhovered() override;
	/** end UCommonButtonBase Parent */
	
private:

	/** Bound Widgets */
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UCommonTextBlock> CommonTextBlock_ButtonText;
	/** Bound Widgets */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Frontend Button", meta = (AllowPrivateAccess = "true"))
	FText ButtonDisplayText;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Frontend Button", meta = (AllowPrivateAccess = "true"))
	bool bUseUpperCaseForButtonText = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Frontend Button", meta = (AllowPrivateAccess = "true"))
	FText ButtonDescriptionText;
};
