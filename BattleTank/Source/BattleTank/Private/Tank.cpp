// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
//#include "TankTrack.h"
#include "Runtime/Engine/Classes/Engine/World.h"



// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Pointer to Aiming Component protected at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

	// Pointer to Movement Component protected at construction
	TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Tank Movement Component"));
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
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}


void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}
/*
void ATank::SetTrackReferences(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	TankMovementComponent->SetLeftTrackReference(LeftTrackToSet);
	TankMovementComponent->SetRightTrackReference(RightTrackToSet);
}*/

void ATank::Fire()
{
	
	auto Time = GetWorld()->GetTimeSeconds();
	
	bool bIsReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadSpeed;
	
	if (Barrel && bIsReloaded) 
	{ 
		// Spawn a projectile at the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint, 
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
		);
		
		if (!Projectile)
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
/*
void ATank::Drive(float Intensity)
{
	TankMovementComponent->Move(Intensity);
}*/