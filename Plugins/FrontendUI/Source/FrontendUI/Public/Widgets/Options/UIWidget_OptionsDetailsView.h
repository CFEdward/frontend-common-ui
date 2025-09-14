// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIWidget_OptionsDetailsView.generated.h"

class UCommonRichTextBlock;
class UCommonLazyImage;
class UCommonTextBlock;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UUIWidget_OptionsDetailsView : public UUserWidget
{
	GENERATED_BODY()

private:

	/*************** Bound Widgets ***************/
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> CommonText_Title;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonLazyImage> CommonLazyImage_Description;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonRichTextBlock> CommonRichText_Description;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonRichTextBlock> CommonRichText_DynamicDetails;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonRichTextBlock> CommonRichText_DisabledReason;
	/*************** Bound Widgets ***************/
};
