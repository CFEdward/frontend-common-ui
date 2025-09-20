// Eduard Ciofu All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "UI_GameUserSettings.generated.h"

UCLASS()
class FRONTENDUI_API UUI_GameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:

	static UUI_GameUserSettings* Get();

	/********** Gameplay Collection Tab **********/
	UFUNCTION()
	FString GetCurrentGameDifficulty() const { return CurrentGameDifficulty; }
	UFUNCTION()
	void SetCurrentGameDifficulty(const FString& InNewGameDifficulty) { CurrentGameDifficulty = InNewGameDifficulty; }
	/********** Gameplay Collection Tab **********/

	/********** Audio Collection Tab **********/
	UFUNCTION()
	FORCEINLINE float GetOverallVolume() const { return OverallVolume; }
	UFUNCTION()
	void SetOverallVolume(const float InVolume);

	UFUNCTION()
	FORCEINLINE float GetMusicVolume() const { return MusicVolume; }
	UFUNCTION()
	void SetMusicVolume(const float InVolume);

	UFUNCTION()
	FORCEINLINE float GetSFXVolume() const { return SFXVolume; }
	UFUNCTION()
	void SetSFXVolume(const float InVolume);

	UFUNCTION()
	FORCEINLINE bool GetBackgroundAudio() const { return bBackgroundAudio; }
	UFUNCTION()
	void SetBackgroundAudio(const bool bInBackgroundAudio);
	/********** Audio Collection Tab **********/
	
private:

	/********** Gameplay Collection Tab **********/
	UPROPERTY(Config)
	FString CurrentGameDifficulty;
	/********** Gameplay Collection Tab **********/

	/********** Audio Collection Tab **********/
	UPROPERTY(Config)
	float OverallVolume{ 1.f };
	UPROPERTY(Config)
	float MusicVolume{ 1.f };
	UPROPERTY(Config)
	float SFXVolume{ 1.f };

	UPROPERTY(Config)
	bool bBackgroundAudio{ false };
	/********** Audio Collection Tab **********/
};
