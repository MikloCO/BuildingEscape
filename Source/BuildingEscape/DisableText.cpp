// Copyright Olivia Mikler 2020


#include "DisableText.h"


// Sets default values for this component's properties
UDisableText::UDisableText()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDisableText::BeginPlay()
{
	Super::BeginPlay();
	ActorThatOpen = GetWorld()->GetFirstPlayerController()->GetPawn();

	
}


// Called every frame
void UDisableText::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpen)) {
		GetOwner()->SetActorHiddenInGame(true);
		//UE_LOG(LogTemp, Error, TEXT("Actor Hidden"));	
	}
}

