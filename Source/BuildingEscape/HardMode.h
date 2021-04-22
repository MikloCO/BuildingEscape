// Copyright Olivia Mikler 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "ShooterGameModeBase.h"
#include "HardMode.generated.h"

/**
 * 
 */
UCLASS()
class BUILDINGESCAPE_API AHardMode : public AShooterGameModeBase
{
	GENERATED_BODY()

public:
	void PawnKilled(APawn* PawnKilled) override;
private:
	void EndGame(bool bIsPlayerWinner);
};
