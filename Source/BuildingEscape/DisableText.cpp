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
	OnHelpHandle();
	GetOwner()->SetActorHiddenInGame(true);
	
}


// Called every frame
void UDisableText::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UDisableText::OnHelpHandle() {
	InputHandle = GetWorld()->GetFirstPlayerController()->FindComponentByClass<UInputComponent>();
	
	if (InputHandle)
	{
		InputHandle->BindAction("Helper", IE_Pressed, this, &UDisableText::HelpOn);
		InputHandle->BindAction("Helper", IE_Released, this, &UDisableText::HelpOff);
	}
}

void UDisableText::HelpOff() {
	GetOwner()->SetActorHiddenInGame(true);
}

void UDisableText::HelpOn() {
	GetOwner()->SetActorHiddenInGame(false);
}


