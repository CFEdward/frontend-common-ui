// Eduard Ciofu All Rights Reserved


#include "Widgets/Components/UI_TabListWidgetBase.h"

#include "Editor/WidgetCompilerLog.h"
#include "Widgets/Components/UI_CommonButtonBase.h"

#if WITH_EDITOR	
void UUI_TabListWidgetBase::ValidateCompiledDefaults(class IWidgetCompilerLog& CompileLog) const
{
	Super::ValidateCompiledDefaults(CompileLog);

	if (!TabButtonEntryWidgetClass)
	{
		CompileLog.Error(FText::FromString(
			TEXT("The variable TabButtonEntryWidgetClass has no valid entry specified. ") +
			GetClass()->GetName() +
			TEXT(" needs a valid entry widget class to function properly."))
		);
	}
}
#endif

void UUI_TabListWidgetBase::RequestRegisterTab(const FName& InTabID, const FText& InTabDisplayName)
{
	RegisterTab(InTabID, TabButtonEntryWidgetClass, nullptr);

	if (const UUI_CommonButtonBase* FoundButton = Cast<UUI_CommonButtonBase>(GetTabButtonBaseByID(InTabID)))
	{
		FoundButton->SetButtonText(InTabDisplayName);
	}
}
