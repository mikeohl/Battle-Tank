// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

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
		ESuggestProjVelocityTraceOption::DoNotTrace // Don't want to trace
	);

	if (bHasAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto ThisTankName = GetOwner()->GetName();
		//UE_LOG(LogTemp, Warning, TEXT("%s Firing at Direction: %s"), *ThisTankName, *AimDirection.ToString());
		MoveBarrel(AimDirection);
	}
		//"%s aiming at: %s from %s"), *ThisTankName, *HitLocation.ToString(), *BarrelLocation.ToString());
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	// Rotate barrel on tank at socket by pitch angle
		// Find difference between current barrel rotation and AimDirection
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;

	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *DeltaRotator.ToString());
	Barrel->Elevate(5.0F); // TODO: Remove magic number placeholder
}