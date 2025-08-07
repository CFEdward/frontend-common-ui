// Eduard Ciofu All Rights Reserved


#include "Widgets/Components/UI_CommonRotator.h"

#include "CommonTextBlock.h"

void UUI_CommonRotator::SetSelectedOptionByText(const FText& InTextOption)
{
	const int32 FoundIndex = TextLabels.IndexOfByPredicate([InTextOption](const FText& TextItem)->bool
		{
			return TextItem.EqualTo(InTextOption);
		}
	);
	
	FoundIndex != INDEX_NONE ? SetSelectedItem(FoundIndex) : MyText->SetText(InTextOption);
}
