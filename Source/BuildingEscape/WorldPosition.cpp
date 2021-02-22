// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();
	/*
	FString Log = TEXT("Yo");
	FString* PtrLog = &Log; //create a pointer
	Log.Len();

	//in order to access value in memory, you neeed to de-reference, 
	(*PtrLog).Len();
	PtrLog->Len();

	UE_LOG(LogTemp, Warning, TEXT("Warning Log"));
	UE_LOG(LogTemp, Warning, TEXT("%s"), **PtrLog); //printing out a memory adress. Complete garbage. You need 2 stars! 1 for overload operator and 1 for de-referencing
	*/
	FString Objectposition = GetOwner()->GetActorLocation().ToString(); //print out x, y, z coordinates
	FString Objectposition2 = GetOwner()->GetActorRotation().ToString();
	FString actorName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("Name of this actor is %s"), *actorName); //Don't use ** (two stars here), only de-reference. :)
	UE_LOG(LogTemp, Warning, TEXT("Name of this actor is %s"), *GetOwner()->GetName());
	UE_LOG(LogTemp, Warning, TEXT("XYZ Coordinates are: [%s][%s]"), *Objectposition, *Objectposition2); // You gotta de-reference to get the value the pointer is pointing too <3
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

