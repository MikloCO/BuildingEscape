// Copyright Olivia Mikler 2020-2021

#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	SetupInputHandle();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

//If physics handle is attached. We want to move the object that we are holding. 

//	GetFirstPhysicsbodyInReach();



}

void UGrabber::Grab() {
UE_LOG(LogTemp, Warning, TEXT("Grabber pressed"));

GetFirstPhysicsbodyInReach();
/*
Only raycast when key is pressed.

Try and reach actors with physicsbody collision channel set.
If we hit something then attach the physics handle.
Attach physics handle
*/

}

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Grabber released"));
	/*
	
	Remove and relese physics handle. 
	*/
}

//Check for Physics handle component
void UGrabber::FindPhysicsHandle() {

PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	InputHandle = GetOwner()->FindComponentByClass<UInputComponent>();
	if (PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("Object '%s' is equipped with physicsHandle"), *(PhysicsHandle->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Object '%s' is missing physicsHandle"), *GetOwner()->GetName());
	}
}

void UGrabber::SetupInputHandle() {
	if (InputHandle)
	{
		//this == A pointer to THIS object, it is the instance of the class that is executing this code. 
		InputHandle->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputHandle->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

/*
void UGrabber::DrawDebugLine(FVector actorVector, FVector LineTraceEnd) {
		// Draw a line from player showing the reach
	

	DrawDebugLine(
		GetWorld(),
		actorVector,
		LineTraceEnd,
		FColor(0, 255, 0),
		false,
		0.f,
		0,
		5.f);
}
*/

FHitResult UGrabber::GetFirstPhysicsbodyInReach() const {
	// Get players viewport
	FVector actorVector; //= GetOwner()->GetActorForwardVector();
	FRotator actorRotator; //= GetOwner()->GetActorRotation();
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT actorVector, OUT actorRotator);

	FVector LineTraceEnd = actorVector + actorRotator.Vector() * reach; 

	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		OUT actorVector,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	AActor* ActorHit = Hit.GetActor();
	if(ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("Actor hit name: %s"), *(ActorHit->GetName()));
	}

	//UE_LOG(LogTemp, Warning, TEXT("Actor hit name: %s"), Hit->GetActor()->GetName());
return Hit;

}