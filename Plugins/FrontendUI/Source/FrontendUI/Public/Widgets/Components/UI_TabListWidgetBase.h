// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonTabListWidgetBase.h"
#include "UI_TabListWidgetBase.generated.h"

class UUI_CommonButtonBase;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UUI_TabListWidgetBase : public UCommonTabListWidgetBase
{
	GENERATED_BODY()

public:

	/** UWidget Parent */
#if WITH_EDITOR	
	virtual void ValidateCompiledDefaults(class IWidgetCompilerLog& CompileLog) const override;
#endif
	/** end UWidget Parent */
	
private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Tab List Settings", meta = (AllowPrivateAccess = "true", ClampMin = "1", ClampMax = "10"))
	int32 DebugEditorPreviewTabCount = 3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Tab List Settings", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUI_CommonButtonBase> TabButtonEntryWidgetClass;
};
