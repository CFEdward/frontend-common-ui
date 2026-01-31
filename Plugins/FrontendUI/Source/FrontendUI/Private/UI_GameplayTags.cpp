// Eduard Ciofu All Rights Reserved

#include "UI_GameplayTags.h"

namespace Frontend
{
	namespace WidgetStack
	{
		UE_DEFINE_GAMEPLAY_TAG(Modal, "Frontend.WidgetStack.Modal");
		UE_DEFINE_GAMEPLAY_TAG(GameMenu, "Frontend.WidgetStack.GameMenu");
		UE_DEFINE_GAMEPLAY_TAG(GameHUD, "Frontend.WidgetStack.GameHUD");
		UE_DEFINE_GAMEPLAY_TAG(Frontend, "Frontend.WidgetStack.Frontend");
	}

	namespace Widget
	{
		UE_DEFINE_GAMEPLAY_TAG(PressAnyKeyScreen, "Frontend.Widget.PressAnyKeyScreen");
		UE_DEFINE_GAMEPLAY_TAG(ConfirmScreen, "Frontend.Widget.ConfirmScreen");
		UE_DEFINE_GAMEPLAY_TAG(MainMenuScreen, "Frontend.Widget.MainMenuScreen");
		UE_DEFINE_GAMEPLAY_TAG(StoryScreen, "Frontend.Widget.StoryScreen");
		UE_DEFINE_GAMEPLAY_TAG(OptionsScreen, "Frontend.Widget.OptionsScreen");
		
		UE_DEFINE_GAMEPLAY_TAG(KeyRemapScreen, "Frontend.Widget.KeyRemapScreen");
	}

	namespace OptionsImages
	{
		UE_DEFINE_GAMEPLAY_TAG(TestImage, "Frontend.OptionsImages.TestImage");
	}
}