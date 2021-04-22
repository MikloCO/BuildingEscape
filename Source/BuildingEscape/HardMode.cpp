// Copyright Olivia Mikler 2020-2021


#include "HardMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "Character/ShooterAIController.h"

void AHardMode::PawnKilled(APawn* PawnKilled) 
{
	Super::PawnKilled(PawnKilled);
	UE_LOG(LogTemp, Warning, TEXT("A pawn was killed"));

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr) {
		EndGame(false);
	}



	for (AShooterAIController* enemyController : TActorRange<AShooterAIController>(GetWorld()))
	{
		if (!enemyController->IsDead())
		{
			return;
		}
		
		EndGame(true);
		
	}
}

void AHardMode::EndGame(bool bIsPlayerWinner) 
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
			
		bool bIsPlayerController = Controller->IsPlayerController();

		bIsPlayerWinner ? Controller->GameHasEnded(Controller->GetPawn(), bIsPlayerController) 
			            : Controller->GameHasEnded(Controller->GetPawn(), !bIsPlayerController);
	}
}