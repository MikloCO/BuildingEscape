// Copyright Olivia Mikler 2020-2021


#include "HardMode.h"

void AHardMode::PawnKilled(APawn* PawnKilled) 
{
	Super::PawnKilled(PawnKilled);
	UE_LOG(LogTemp, Warning, TEXT("A pawn was killed"));

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr) {
		PlayerController->GameHasEnded(nullptr, false);
	}
}