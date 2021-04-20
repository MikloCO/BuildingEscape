// Copyright Olivia Mikler 2020-2021

#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "AITypes.h"
#include "BehaviorTree/BlackboardComponent.h"


void AShooterAIController::BeginPlay() 
{
	Super::BeginPlay();


	if (AIBehavior != nullptr) 
	{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		RunBehaviorTree(AIBehavior);
	}
}

	void AShooterAIController::Tick(float DeltaSeconds) 
	{
		Super::Tick(DeltaSeconds);
	}