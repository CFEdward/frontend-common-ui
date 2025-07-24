// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UI_ListDataObject_Base.h"
#include "UI_ListDataObject_Collection.generated.h"

UCLASS()
class FRONTENDUI_API UUI_ListDataObject_Collection : public UUI_ListDataObject_Base
{
	GENERATED_BODY()

public:

	/** UUI_ListDataObject_Base Parent */
	virtual TArray<UUI_ListDataObject_Base*> GetAllChildListData() const override;
	virtual bool HasAnyChildListData() const override;
	/** end UUI_ListDataObject_Base Parent */

	void AddChildListData(UUI_ListDataObject_Base* InChildListData);
	
private:

	UPROPERTY(Transient)
	TArray<TObjectPtr<UUI_ListDataObject_Base>> ChildListDataArray;
};
