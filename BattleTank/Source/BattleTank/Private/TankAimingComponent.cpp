// Copyright Michael Ohl 2018-2019

#include "TankAimingComponent.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("%s: Aiming Component Begin Play"), *(GetOwner()->GetName()))
	LastFireTime = GetWorld()->GetTimeSeconds();
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (FiringStatus == EFiringState::OutOfAmmo) { return; }
	if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadSpeed)
	{
		FiringStatus = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringStatus = EFiringState::Aiming;
	}
	else
	{
		FiringStatus = EFiringState::Locked;
	}
}

void UTankAimingComponent::InitializeAimingComponent(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet)
{
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(const FVector& HitLocation) 
{
	if (!ensure(Barrel)) { return; }

	// Projectile properties
	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	
	bool bHasAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this, 
		OutLaunchVelocity, // Direction to fire 
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.0F,
		0.0F,
		ESuggestProjVelocityTraceOption::DoNotTrace // Don't want to trace
	);

	if (bHasAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();

		MoveTurret(AimDirection);
		MoveBarrel(AimDirection);

		// UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found"), GetWorld()->GetTimeSeconds());
		// UE_LOG(LogTemp, Warning, TEXT("%s Firing at Direction: %s"), *(GetOwner()->GetName()), *AimDirection.ToString());
	}
	// else { UE_LOG(LogTemp, Warning, TEXT("%f: No aim solution found"), GetWorld()->GetTimeSeconds()); }
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	return !Barrel->GetForwardVector().Equals(AimDirection, 0.01f);
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBlueprint)) { return; }

	if (FiringStatus != EFiringState::Reloading && FiringStatus != EFiringState::OutOfAmmo)
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
		AmmoCount--;
		if (AmmoCount <= 0)
		{
			FiringStatus = EFiringState::OutOfAmmo;
		}

		auto ThisTankName = GetName();
		//UE_LOG(LogTemp, Warning, TEXT("%s: Fired projectile at time: %f"), *ThisTankName, Time);
	}

}

// Rotate barrel on tank at socket by pitch angle
void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	if (!ensure(Barrel)) { return; }

	// Find difference between current barrel rotation and AimDirection
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;

	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *DeltaRotator.ToString());
	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurret(FVector AimDirection)
{
	if (!ensure(Turret)) { return; }

	auto TurretRotation = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - TurretRotation;

	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *DeltaRotator.ToString());

	// Ensure Shortest Route
	if (FMath::Abs(DeltaRotator.Yaw) >= 180.0f)
	{
		DeltaRotator.Yaw = -DeltaRotator.Yaw;
	}

	Turret->Rotate(DeltaRotator.Yaw);
}

EFiringState UTankAimingComponent::GetFiringState()
{
	return FiringStatus;
}

FString UTankAimingComponent::GetAmmoCount()
{
	FString Ammo = FString(TEXT("Ammo: "));
	Ammo.AppendInt(AmmoCount);
	return  Ammo;
}