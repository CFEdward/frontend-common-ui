// Eduard Ciofu All Rights Reserved


#include "Controllers/UI_PlayerController.h"

#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

void AUI_PlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	TArray<AActor*> FoundCameras;
	UGameplayStatics::GetAllActorsOfClassWithTag(this, ACameraActor::StaticClass(), FName("Default"), FoundCameras);

	if (!FoundCameras.IsEmpty())
	{
		SetViewTarget(FoundCameras[0]);
	}
}
