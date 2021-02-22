// Copyright Olivia Mikler 2020-2021

#include "Grabber.h"

#define OUT



// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber is available"));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	// Get players viewport
	FVector actorVector = GetOwner()->GetActorForwardVector();
	FRotator actorRotator = GetOwner()->GetActorRotation();
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT actorVector, OUT actorRotator);

	//Logging out to test
	//UE_LOG(LogTemp, Warning, TEXT("ActorVector: %s ActorRotator: %s"), *actorVector.ToString(), *actorRotator.ToString());
	

	// Draw a line from player showing the reach

	FVector LineTraceEnd = actorVector + actorRotator.Vector() * reach; //FVector(actorVector.ForwardVector.X + reach, actorVector.ForwardVector.Y + reach, 0.f);

	DrawDebugLine(
		GetWorld(),
		actorVector,
		LineTraceEnd,
		FColor(0, 255, 0),
		false,
		0.f,
		0,
		5.f
	);
	//Raycast out to a certain distance (Reach)
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		OUT actorVector,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams

		);
	
	//UE_LOG(LogTemp, Warning, TEXT("Actor hit name: %s"), Hit->GetActor()->GetName());
	
	AActor* ActorHit = Hit.GetActor();
	if(ActorHit)
	UE_LOG(LogTemp, Error, TEXT("You hit: %s"), *(ActorHit->GetName()));
														
	

//	UE_LOG(LogTemp, Warning, TEXT("ActorVector: %s"), *GetWorld()->Hit.Actor()->GetName());
	
	
	

}

//Log out all we raycast


	//Ray-cast out to certain distance (reach)
	

	//See what it hits. 

	


