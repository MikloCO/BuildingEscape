// Copyright Olivia Mikler 2020-2021

#pragma once

#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float reach{ 200.f };

	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandle{ nullptr };
	UPROPERTY()
	UInputComponent* InputHandle { nullptr };

	void Grab();
	void Release();
	void FindPhysicsHandle();
	void OnActionInputHandle();
	//void DrawDebugLine(FVector actorVector, FVector LineTraceEnd);
	FHitResult GetFirstPhysicsbodyInReach() const;
	FVector GetPlayerCalculatedRayTraceEnd() const;
	FVector GetPlayersWorldPos() const;
		
};
