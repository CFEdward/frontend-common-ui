// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UIWidget_ActivatableBase.h"
#include "UITypes/UIEnumTypes.h"
#include "UIWidget_ConfirmScreen.generated.h"

class UDynamicEntryBox;
class UCommonTextBlock;

USTRUCT(BlueprintType)
struct FConfirmScreenButtonInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EConfirmScreenButtonType ConfirmScreenButtonType = EConfirmScreenButtonType::Unknown;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ButtonTextToDisplay = FText::GetEmpty();
};

UCLASS()
class FRONTENDUI_API UUI_ConfirmScreenInfoObject : public UObject
{
	GENERATED_BODY()

public:

	static UUI_ConfirmScreenInfoObject* CreateOKScreen(const FText& InScreenTitle, const FText& InScreenMessage);
	static UUI_ConfirmScreenInfoObject* CreateYesNoScreen(const FText& InScreenTitle, const FText& InScreenMessage);
	static UUI_ConfirmScreenInfoObject* CreateOKCancelScreen(const FText& InScreenTitle, const FText& InScreenMessage);

	UPROPERTY(Transient)
	FText ScreenTitle = FText::GetEmpty();
	UPROPERTY(Transient)
	FText ScreenMessage = FText::GetEmpty();

	UPROPERTY(Transient)
	TArray<FConfirmScreenButtonInfo> AvailableScreenButtons;
};

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UUIWidget_ConfirmScreen : public UUIWidget_ActivatableBase
{
	GENERATED_BODY()

private:
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> CommonTextBlock_Title;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> CommonTextBlock_Message;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDynamicEntryBox> DynamicEntryBox_Buttons;
};
