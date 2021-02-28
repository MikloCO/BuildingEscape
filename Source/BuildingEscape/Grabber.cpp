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
	OnActionInputHandle();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//If physics handle is attached. We want to move the object that we are holding. 
	if (PhysicsHandle != nullptr && PhysicsHandle->GrabbedComponent) {
		PhysicsHandle->SetTargetLocation(GetPlayerCalculatedRayTraceEnd());
	}
}

void UGrabber::FindPhysicsHandle() {
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>(); 

	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Object '%s' is missing physicsHandle"), *(PhysicsHandle->GetName()));
	}
}

void UGrabber::OnActionInputHandle() {
	InputHandle = GetOwner()->FindComponentByClass<UInputComponent>(); 
	if (InputHandle)
	{
		InputHandle->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputHandle->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

void UGrabber::Grab() {
//	UE_LOG(LogTemp, Warning, TEXT("Grabber pressed"));

	GetPlayerCalculatedRayTraceEnd();

	FHitResult HitResult = GetFirstPhysicsbodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	AActor* ActorHit{ HitResult.GetActor() };
	
	if (PhysicsHandle != nullptr && ActorHit) {
		PhysicsHandle->GrabComponentAtLocation(ComponentToGrab, NAME_None, GetPlayerCalculatedRayTraceEnd());
	}
}

void UGrabber::Release() {
	if (PhysicsHandle != nullptr) 
		PhysicsHandle->ReleaseComponent();
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
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetPlayersWorldPos(),
		GetPlayerCalculatedRayTraceEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
	return Hit;
}

FVector UGrabber::GetPlayerCalculatedRayTraceEnd() const {
	
	FVector PlayerViewPos;
	FRotator PlayerViewPointRot;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPos,
		OUT PlayerViewPointRot
	);
	return PlayerViewPos + PlayerViewPointRot.Vector() * reach;
}

FVector UGrabber::GetPlayersWorldPos() const {
	FVector actorLocation;
	FRotator actorRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT actorLocation,
		OUT actorRotation
	);
	return actorLocation;
}
