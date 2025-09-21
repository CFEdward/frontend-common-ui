#pragma once

#include "UI_StructTypes.generated.h"

USTRUCT()
struct FOptionsDataEditConditionDescriptor
{
	GENERATED_BODY()

public:

	FORCEINLINE void SetEditConditionFunc(const TFunction<bool()>& InEditConditionFunc) { EditConditionFunc = InEditConditionFunc; }
	FORCEINLINE bool IsValid() const { return EditConditionFunc != nullptr; }
	bool IsEditConditionMet() const { return IsValid() ? EditConditionFunc() : true; }
	FORCEINLINE FString GetDisabledRichReason() const { return DisabledRichReason; }
	FORCEINLINE void SetDisabledRichReason(const FString& InReachReason) { DisabledRichReason = InReachReason; }
	bool HasForcedStringValue() const { return DisabledForcedStringValue.IsSet(); }
	FString GetDisabledForcedStringValue() const { return DisabledForcedStringValue.GetValue(); }
	FORCEINLINE void SetDisabledForcedStringValue(const FString& InForcedValue) { DisabledForcedStringValue = InForcedValue; }
	
private:

	TFunction<bool()> EditConditionFunc;
	FString DisabledRichReason;
	TOptional<FString> DisabledForcedStringValue;
};