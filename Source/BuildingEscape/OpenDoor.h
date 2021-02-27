// Copyright Olivia Mikler 2020-2021
#pragma once

//#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "UObject/UObjectBaseUtility.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "GameFrameWork/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "OpenDoor.generated.h"



UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOpenDoor();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	float GetTotalMassOfActors() const;

private:
	float InitialYaw;
	float CurrentYaw;
	float DoorLastOpened{ 0.f };
	UPROPERTY(EditAnywhere)
		float MassToOpenDoor{ 60.f };

	UPROPERTY(EditAnywhere) //Edit in editor. 
		float OpenAngle{ 90.f };

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
		//We can be generic and use AActor instead of Pawn.
		AActor* ActorThatOpen;

	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);

	UPROPERTY(EditAnywhere)
		float DoorCloseDelay{ .5f };
	UPROPERTY(EditAnywhere)
		float DoorOpenSpeed{ .8f };
	UPROPERTY(EditAnywhere)
		float DoorCloseSpeed{ 2.f };
	//UPROPERTY(EditAnywhere)
	//	float TotalMass { 0.f };

};
