// Copyright Olivia Mikler 2020-2021
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Gun.h"

#define COLLISION_GUN ECC_Bullet

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject< USkeletalMeshComponent>(TEXT("Base Mesh"));
	Mesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger() {
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlare, Mesh, TEXT("MuzzleFlashSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return; 
	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) return;

	FVector Location;
	FRotator Rotation;

	OwnerController->GetPlayerViewPoint(Location, Rotation);

	FVector End = Location + Rotation.Vector() * MaxRange;

	FHitResult point;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	bool bBulletHit = GetWorld()->LineTraceSingleByChannel(
		OUT point,
		Location,
		End,
		ECollisionChannel::ECC_GameTraceChannel1,
		Params
	);

	if (bBulletHit) {
		FVector ShotDirection = -Rotation.Vector();
	
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			BulletHit,
			point.Location,
			ShotDirection.Rotation()
		);
		
		AActor* HitCharacter = point.GetActor();

		if (HitCharacter != nullptr) {
			FPointDamageEvent DamageEvent(damage, point, ShotDirection, nullptr);
			HitCharacter->TakeDamage(
				damage,
				DamageEvent,
				OwnerController,
				this
			);

			
		}


		
	}


	
}