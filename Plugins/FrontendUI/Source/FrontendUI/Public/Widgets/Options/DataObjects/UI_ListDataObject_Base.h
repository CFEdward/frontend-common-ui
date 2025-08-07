// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UITypes/UIEnumTypes.h"
#include "UObject/Object.h"
#include "UI_ListDataObject_Base.generated.h"

#define LIST_DATA_ACCESSOR(DataType, PropertyName)													\
	FORCEINLINE DataType Get##PropertyName() const { return PropertyName; }							\
	void Set##PropertyName(const DataType& In##PropertyName) { PropertyName = In##PropertyName; }

UCLASS(Abstract)
class FRONTENDUI_API UUI_ListDataObject_Base : public UObject
{
	GENERATED_BODY()

public:

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnListDataModified, UUI_ListDataObject_Base*, EOptionsListDataModifyReason);

	void InitDataObject();
	
	/**
	 * Empty in the base class. Child class ListDataObject_Collection should override it.
	 * The function should return all the child data a tab has
	 */
	virtual TArray<UUI_ListDataObject_Base*> GetAllChildListData() const { return TArray<UUI_ListDataObject_Base*>(); }
	virtual bool HasAnyChildListData() const { return false; }

	FOnListDataModified OnListDataModified;

	LIST_DATA_ACCESSOR(FName, DataID);
	LIST_DATA_ACCESSOR(FText, DataDisplayName);
	LIST_DATA_ACCESSOR(FText, DescriptionRichText);
	LIST_DATA_ACCESSOR(FText, DisabledRichText);
	LIST_DATA_ACCESSOR(TSoftObjectPtr<UTexture2D>, SoftDescriptionImage);
	LIST_DATA_ACCESSOR(TObjectPtr<UUI_ListDataObject_Base>, ParentData);

protected:

	/** Empty in base class. The child classes should override it to handle the initialization needed accordingly */
	virtual void OnDataObjectInitialized() {}

	virtual void NotifyListDataModified(UUI_ListDataObject_Base* ModifiedData, const EOptionsListDataModifyReason ModifyReason = EOptionsListDataModifyReason::DirectlyModified);
	
private:

	FName DataID;
	FText DataDisplayName;
	FText DescriptionRichText;
	FText DisabledRichText;
	TSoftObjectPtr<UTexture2D> SoftDescriptionImage;

	UPROPERTY(Transient)
	TObjectPtr<UUI_ListDataObject_Base> ParentData;
};
