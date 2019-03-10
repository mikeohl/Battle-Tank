// Copyright Michael Ohl 2018-2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward Declarations
class UTankAimingComponent;
class UTankBarrel;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Set the tank to Aim at HitLocation
	void AimAt(const FVector& HitLocation) const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

private:

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000.0f; // 4000 m/s -> TODO: Find sensible value

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadSpeed = 3.0f; // in seconds

	double LastFireTime = -5.0;

	// Local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr;
	
};
