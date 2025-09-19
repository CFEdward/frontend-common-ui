// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonListView.h"
#include "UI_CommonListView.generated.h"

class UUI_DataAsset_DataListEntryMapping;

UCLASS()
class FRONTENDUI_API UUI_CommonListView : public UCommonListView
{
	GENERATED_BODY()

public:

	/** UWidget Parent */
#if WITH_EDITOR	
	virtual void ValidateCompiledDefaults(class IWidgetCompilerLog& CompileLog) const override;
#endif
	/** end UWidget Parent */

protected:
	
	/** UListView Parent */
	virtual bool OnIsSelectableOrNavigableInternal(UObject* FirstSelectedItem) override;
	/** end UListView Parent */
	/** UCommonListView Parent */
	virtual UUserWidget& OnGenerateEntryWidgetInternal(UObject* Item, TSubclassOf<UUserWidget> DesiredEntryClass, const TSharedRef<STableViewBase>& OwnerTable) override;
	/** end UCommonListView Parent */
	
private:

	UPROPERTY(EditAnywhere, Category = "Frontend List View Settings")
	TObjectPtr<UUI_DataAsset_DataListEntryMapping> DataListEntryMapping;
};
