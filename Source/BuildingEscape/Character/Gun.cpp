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
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));

	FHitResult Hit;
	FVector ShotDirection;

	bool bBulletHit = GunTrace(Hit, ShotDirection);

	if (bBulletHit) {
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			BulletHit,
			Hit.Location,
			ShotDirection.Rotation()
		);

		UGameplayStatics::PlaySoundAtLocation(
			GetWorld(),
			ImpactSound,
			Hit.Location
		);
		
		AActor* HitCharacter = Hit.GetActor();

		if (HitCharacter != nullptr) {
			FPointDamageEvent DamageEvent(damage, Hit, ShotDirection, nullptr);
			AController* OwnerController = GetOwnerController();
			HitCharacter->TakeDamage(
				damage,
				DamageEvent,
				OwnerController,
				this
			);
		}		
	}
}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr) 
	{
		return false;
	}

	FVector Location;
	FRotator Rotation;

	OwnerController->GetPlayerViewPoint(Location, Rotation);

	ShotDirection = -Rotation.Vector();

	FVector End = Location + Rotation.Vector() * MaxRange;
	
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return 
		GetWorld()->LineTraceSingleByChannel(
		OUT Hit,
		Location,
		End,
		ECollisionChannel::ECC_GameTraceChannel1,
		Params
	);
}

AController* AGun::GetOwnerController() const 
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) 
	{
		return nullptr;
	}
	
	return OwnerPawn->GetController();

}