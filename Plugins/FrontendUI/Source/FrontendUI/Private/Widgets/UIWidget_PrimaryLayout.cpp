// Eduard Ciofu All Rights Reserved


#include "Widgets/UIWidget_PrimaryLayout.h"

#include "UI_DebugHelper.h"

UCommonActivatableWidgetContainerBase* UUIWidget_PrimaryLayout::FindWidgetStackByTag(const FGameplayTag& InTag) const
{
	checkf(RegisteredWidgetStackMap.Contains(InTag), TEXT("Can not find the Widget Stack by the tag %s"), *InTag.ToString());

	return RegisteredWidgetStackMap.FindRef(InTag);
}

void UUIWidget_PrimaryLayout::RegisterWidgetStack(const FGameplayTag InStackTag, UCommonActivatableWidgetContainerBase* InStack)
{
	if (!IsDesignTime())
	{
		if (!RegisteredWidgetStackMap.Contains(InStackTag))
		{
			RegisteredWidgetStackMap.Add(InStackTag, InStack);

			Debug::Print(TEXT("Widget Stack Registered under the tag ") + InStackTag.ToString());
		}
	}
}
