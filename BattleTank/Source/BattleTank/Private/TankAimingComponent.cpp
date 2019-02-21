// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	//Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	//Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(const FVector& HitLocation, const float LaunchSpeed) 
{
	if (!Barrel) { return; }

	// Projectile properties
	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// Calculate the OutLaunchVelocity
	//auto AimDirection = OutLaunchVelocity.GetSafeNormal();
	auto ThisTankName = GetOwner()->GetName();
	
	//UE_LOG(LogTemp, Warning, TEXT("Firing at Speed: %f"), LaunchSpeed);
	
	bool bHasAimSolution = UGameplayStatics::SuggestProjectileVelocity(
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
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto ThisTankName = GetOwner()->GetName();
		//UE_LOG(LogTemp, Warning, TEXT("%s Firing at Direction: %s"), *ThisTankName, *AimDirection.ToString());
		MoveTurret(AimDirection);
		MoveBarrel(AimDirection);
		auto Time = GetWorld()->GetTimeSeconds();
		// UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found"), Time);
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		// UE_LOG(LogTemp, Warning, TEXT("%f: No aim solution found"), Time);
	}
		//"%s aiming at: %s from %s"), *ThisTankName, *HitLocation.ToString(), *BarrelLocation.ToString());
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	if (!BarrelToSet) { return; }
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	if (!TurretToSet) { return; }
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	// Rotate barrel on tank at socket by pitch angle
	// Find difference between current barrel rotation and AimDirection
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;

	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *DeltaRotator.ToString());
	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurret(FVector AimDirection)
{
	auto TurretRotation = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - TurretRotation;

	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *DeltaRotator.ToString());
	Turret->Rotate(DeltaRotator.Yaw);
}