// Copyright Olivia Mikler 2020-2021


#include "SwitchScene.h"

// Sets default values for this component's properties
USwitchScene::USwitchScene()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USwitchScene::BeginPlay()
{
	Super::BeginPlay();

//Find SwitchScene plate (if not empty)
	try {
		ActorToSwitchScene = GetWorld()->GetFirstPlayerController()->GetPawn();
	}	catch (const std::nullptr_t) {	
		UE_LOG(LogTemp, Error, TEXT("There is no FPS controller in the scene!"));
	}
	
}


// Called every frame
void USwitchScene::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (Switchlevel && Switchlevel->IsOverlappingActor(ActorToSwitchScene)) {
		UGameplayStatics::OpenLevel(
			this, 
			TEXT("ShooterTokyoDay"), 
			true
		);
	}

}

//Has player stepped upon Switchscene pressureplate? If yes, load next scene. 

