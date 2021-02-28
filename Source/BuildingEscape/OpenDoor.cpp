// Copyright Olivia Mikler 2020-2021

#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	OpenAngle += InitialYaw;

	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("%s, has no pressureplate."), *GetOwner()->GetName());
	}
}

void UOpenDoor::FindAudioComponent()  {
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (AudioComponent == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("%s is missing Audio component."), *GetOwner()->GetName());
	}

	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(GetTotalMassOfActors() > MassToOpenDoor) {
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}

	else if (GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay) {
				CloseDoor(DeltaTime);
	}	
}

void UOpenDoor::OpenDoor(float DeltaTime) {
	CurrentYaw = FMath::Lerp(CurrentYaw, OpenAngle, DeltaTime * DoorOpenSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

	AudioComponent->Play();
}

void UOpenDoor::CloseDoor(float DeltaTime) {
	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime * DoorCloseSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);


}

float UOpenDoor::GetTotalMassOfActors() const {

	float TotalMass = 0.f; 
	// Find all overlapping actors
	TArray<AActor*> OverlappingActors;

	if (PressurePlate != nullptr) {
		PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s, has no pressureplate."), *GetOwner()->GetName());
	}
	
	for (AActor* Actor : OverlappingActors) {
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	// UE_LOG(LogTemp, Error, TEXT("Total mass %f"), TotalMass);
	
	return TotalMass;
}