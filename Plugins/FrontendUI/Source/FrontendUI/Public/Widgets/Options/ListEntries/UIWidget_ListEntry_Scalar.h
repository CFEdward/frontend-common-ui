// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UIWidget_ListEntry_Base.h"
#include "UIWidget_ListEntry_Scalar.generated.h"

class UUI_ListDataObject_Scalar;
class UAnalogSlider;
class UCommonNumericTextBlock;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UUIWidget_ListEntry_Scalar : public UUIWidget_ListEntry_Base
{
	GENERATED_BODY()

protected:

	/** UUserWidget Parent */
	virtual void NativeOnInitialized() override;
	/** end UUserWidget Parent */

	/** UUIWidget_ListEntry_Base Parent */
	virtual void OnOwningListDataObjectSet(UUI_ListDataObject_Base* InOwningListDataObject) override;
	virtual void OnOwningListDataObjectModified(UUI_ListDataObject_Base* OwningModifiedData, EOptionsListDataModifyReason ModifyReason) override;
	/** end UUIWidget_ListEntry_Base Parent */

private:

	UFUNCTION()
	void OnSliderValueChanged(const float Value);
	UFUNCTION()
	void OnSliderMouseEnd();

	/*************** Bound Widgets ***************/
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UCommonNumericTextBlock> CommonNumeric_SettingValue;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UAnalogSlider> AnalogSlider_Setting;
	/*************** Bound Widgets ***************/

	UPROPERTY(Transient)
	TObjectPtr<UUI_ListDataObject_Scalar> CachedOwningScalarDataObject;
};
