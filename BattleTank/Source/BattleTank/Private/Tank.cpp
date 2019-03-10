// Copyright Michael Ohl 2018-2019

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Engine/World.h"



// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(const FVector& HitLocation) const
{
	//auto ThisTankName = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at: %s"), *ThisTankName, *HitLocation.ToString());

	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	if (!ensure(Barrel)) { return; }
	
	auto Time = GetWorld()->GetTimeSeconds();
	
	bool bIsReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadSpeed;
	
	if (bIsReloaded) 
	{ 
		// Spawn a projectile at the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint, 
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
		);
		
		if (!ensure(Projectile))
		{
			UE_LOG(LogTemp, Warning, TEXT("No Projectile!"));
			return;
		}
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();

		auto ThisTankName = GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s: Fired projectile at time: %f"), *ThisTankName, Time);
	}
	
}