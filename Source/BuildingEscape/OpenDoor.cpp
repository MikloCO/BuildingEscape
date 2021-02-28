// Copyright Olivia Mikler 2020-2021

#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	OpenAngle += InitialYaw;

	FindPressurePlate();
	FindAudioComponent();
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

	CloseDoorSoundHasPlayed = false;

	if (AudioComponent != nullptr && !OpenDoorSoundHasPlayed) {
		AudioComponent->Play(0.2f);
		OpenDoorSoundHasPlayed = true;
	}
	
}

void UOpenDoor::CloseDoor(float DeltaTime) {
	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime * DoorCloseSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

	OpenDoorSoundHasPlayed = false;
	if(AudioComponent != nullptr && !CloseDoorSoundHasPlayed) {
		AudioComponent->Play(0.2f);
		CloseDoorSoundHasPlayed = true;
		UE_LOG(LogTemp, Error, TEXT("Audiocomponent is not playing."));
	}

}

float UOpenDoor::GetTotalMassOfActors() const {

	float TotalMass = 0.f; 
	TArray<AActor*> OverlappingActors;

	if (PressurePlate != nullptr) {
		PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	}
	
	for (AActor* Actor : OverlappingActors) {
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	
	return TotalMass;
}

void UOpenDoor::FindPressurePlate() {
	if (PressurePlate == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("%s, has no pressureplate."), *GetOwner()->GetName());
	}
}

void UOpenDoor::FindAudioComponent()  {
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!AudioComponent) {
		UE_LOG(LogTemp, Error, TEXT("%s is missing Audio component."), *GetOwner()->GetName());
	}
}