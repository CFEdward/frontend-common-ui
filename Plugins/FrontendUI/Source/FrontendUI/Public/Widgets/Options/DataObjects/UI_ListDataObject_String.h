// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UI_ListDataObject_Value.h"
#include "UI_ListDataObject_String.generated.h"

UCLASS()
class FRONTENDUI_API UUI_ListDataObject_String : public UUI_ListDataObject_Value
{
	GENERATED_BODY()

public:

	void AddDynamicOption(const FString& InStringValue, const FText& InDisplayText);
	void AdvanceToNextOption();
	void BackToPreviousOption();
	void OnRotatorInitiatedValueChange(const FText& InNewSelectedText);

	FORCEINLINE FText GetCurrentDisplayText() const { return CurrentDisplayText; }
	FORCEINLINE const TArray<FText>& GetAvailableOptionsTextArray() const { return AvailableOptionsTextArray; }
	
protected:

	/** UUI_ListDataObject_Base Parent */
	virtual void OnDataObjectInitialized() override;
	virtual bool CanResetBackToDefaultValue() const override;
	virtual bool TryResetBackToDefaultValue() override;
	/** end UUI_ListDataObject_Base Parent */

	bool TrySetDisplayTextFromStringValue(const FString& InStringValue);
	
	FString CurrentStringValue;
	FText CurrentDisplayText;
	TArray<FString> AvailableOptionsStringArray;
	TArray<FText> AvailableOptionsTextArray;
};

UCLASS()
class FRONTENDUI_API UUI_ListDataObject_StringBool : public UUI_ListDataObject_String
{
	GENERATED_BODY()

public:

	void OverrideTrueDisplayText(const FText& InNewTrueDisplayText);
	void OverrideFalseDisplayText(const FText& InNewFalseDisplayText);

	void SetTrueAsDefaultValue();
	void SetFalseAsDefaultValue();

protected:

	/** UUI_ListDataObject_String Parent */
	virtual void OnDataObjectInitialized() override;
	/** end UUI_ListDataObject_String Parent */
	
private:

	void TryInitBoolValues();

	const FString TrueString{ TEXT("true") };
	const FString FalseString{ TEXT("false") };
};

UCLASS()
class FRONTENDUI_API UUI_ListDataObject_StringEnum : public UUI_ListDataObject_String
{
	GENERATED_BODY()

public:

	template<typename EnumType>
	void AddEnumOption(EnumType InEnumOption, const FText& InDisplayText);
	
	template<typename EnumType>
	EnumType GetCurrentValueAsEnum() const;
	template<typename EnumType>
	void SetDefaultValueFromEnumOption(const EnumType InEnumOption);
};

template <typename EnumType>
void UUI_ListDataObject_StringEnum::AddEnumOption(EnumType InEnumOption, const FText& InDisplayText)
{
	const UEnum* StaticEnumOption = StaticEnum<EnumType>();
	const FString ConvertedEnumString = StaticEnumOption->GetNameStringByValue(InEnumOption);

	AddDynamicOption(ConvertedEnumString, InDisplayText);
}

template <typename EnumType>
EnumType UUI_ListDataObject_StringEnum::GetCurrentValueAsEnum() const
{
	const UEnum* StaticEnumOption = StaticEnum<EnumType>();
	
	return (EnumType)StaticEnumOption->GetValueByNameString(CurrentStringValue);
}

template <typename EnumType>
void UUI_ListDataObject_StringEnum::SetDefaultValueFromEnumOption(const EnumType InEnumOption)
{
	const UEnum* StaticEnumOption = StaticEnum<EnumType>();
	const FString ConvertedEnumString = StaticEnumOption->GetNameStringByValue(InEnumOption);

	SetDefaultValueFromString(ConvertedEnumString);
}
