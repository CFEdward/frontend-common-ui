// Eduard Ciofu All Rights Reserved


#include "Widgets/Components/UI_CommonListView.h"

#include "Editor/WidgetCompilerLog.h"
#include "Widgets/Options/UI_DataAsset_DataListEntryMapping.h"
#include "Widgets/Options/DataObjects/UI_ListDataObject_Base.h"
#include "Widgets/Options/ListEntries/UIWidget_ListEntry_Base.h"

#if WITH_EDITOR	
void UUI_CommonListView::ValidateCompiledDefaults(class IWidgetCompilerLog& CompileLog) const
{
	Super::ValidateCompiledDefaults(CompileLog);

	if (!DataListEntryMapping)
	{
		CompileLog.Error(FText::FromString(
			TEXT("The variable DataListEntryMapping has no valid data asset assigned, ") +
			GetClass()->GetName() +
			TEXT(" needs a valid data asset to function properly.")
		));
	}
}
#endif

UUserWidget& UUI_CommonListView::OnGenerateEntryWidgetInternal(UObject* Item, TSubclassOf<UUserWidget> DesiredEntryClass, const TSharedRef<STableViewBase>& OwnerTable)
{
	if (IsDesignTime())
	{
		return Super::OnGenerateEntryWidgetInternal(Item, DesiredEntryClass, OwnerTable);
	}
	if (const TSubclassOf<UUIWidget_ListEntry_Base> FoundWidgetClass = DataListEntryMapping->FindEntryWidgetClassByDataObject(CastChecked<UUI_ListDataObject_Base>(Item)))
	{
		return GenerateTypedEntry<UUIWidget_ListEntry_Base>(FoundWidgetClass, OwnerTable);
	}
	else
	{
		return Super::OnGenerateEntryWidgetInternal(Item, DesiredEntryClass, OwnerTable);
	}
}
