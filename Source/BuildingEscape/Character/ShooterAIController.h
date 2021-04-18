// Copyright Olivia Mikler 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class BUILDINGESCAPE_API AShooterAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;


};
