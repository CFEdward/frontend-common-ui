// Eduard Ciofu All Rights Reserved


#include "Widgets/Options/UIWidget_OptionsDetailsView.h"

#include "CommonLazyImage.h"
#include "CommonRichTextBlock.h"
#include "CommonTextBlock.h"
#include "Widgets/Options/DataObjects/UI_ListDataObject_Base.h"

void UUIWidget_OptionsDetailsView::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ClearDetailsViewInfo();
}

void UUIWidget_OptionsDetailsView::UpdateDetailsViewInfo(UUI_ListDataObject_Base* InDataObject, const FString& InEntryWidgetClassName) const
{
	if (!InDataObject) return;

	CommonText_Title->SetText(InDataObject->GetDataDisplayName());
	if (!InDataObject->GetSoftDescriptionImage().IsNull())
	{
		CommonLazyImage_Description->SetBrushFromLazyTexture(InDataObject->GetSoftDescriptionImage());
		CommonLazyImage_Description->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		CommonLazyImage_Description->SetVisibility(ESlateVisibility::Collapsed);
	}
	
	CommonRichText_Description->SetText(InDataObject->GetDescriptionRichText());
	const FString DynamicDetails = FString::Printf(
		TEXT("Data Object Class: <Bold>%s</>\n\nEntry Widget Class: <Bold>%s</>"),
		*InDataObject->GetClass()->GetName(),
		*InEntryWidgetClassName
	);
	CommonRichText_DynamicDetails->SetText(FText::FromString(DynamicDetails));
	CommonRichText_DisabledReason->SetText(InDataObject->IsDataCurrentlyEditable() ? FText::GetEmpty() : InDataObject->GetDisabledRichText());
}

void UUIWidget_OptionsDetailsView::ClearDetailsViewInfo() const
{
	CommonText_Title->SetText(FText::GetEmpty());
	CommonLazyImage_Description->SetVisibility(ESlateVisibility::Collapsed);
	CommonRichText_Description->SetText(FText::GetEmpty());
	CommonRichText_DynamicDetails->SetText(FText::GetEmpty());
	CommonRichText_DisabledReason->SetText(FText::GetEmpty());
}
