// Copyright Olivia Mikler 2020-2021

#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "AITypes.h"


void AShooterAIController::BeginPlay() 
{
	Super::BeginPlay();

}


	void AShooterAIController::Tick(float DeltaSeconds) 
	{
		APawn* PlayerPawn{ UGameplayStatics::GetPlayerPawn(GetWorld(), 0) };
		MoveToActor(PlayerPawn);
		SetFocus(PlayerPawn, 200);	
	}