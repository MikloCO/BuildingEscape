// Copyright Olivia Mikler 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BUILDINGESCAPE_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;
	
private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> HUDClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> LoseScreenClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> WinScreenClass;

	UPROPERTY(EditAnywhere)
		float RestartDelay = 5.0f;
	
	FTimerHandle RestartTimer;

	UPROPERTY(EditAnywhere)
		UUserWidget* HUD;

protected:
	virtual void BeginPlay() override;
};
