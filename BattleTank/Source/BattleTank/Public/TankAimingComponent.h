// Copyright Michael Ohl 2018-2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading, Aiming, Locked
};

// Forward Declarations
class UTankBarrel; 
class UTankTurret;
class AProjectile;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void InitializeAimingComponent(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet);

	void AimAt(const FVector& HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	void MoveBarrel(FVector AimDirection);
	void MoveTurret(FVector AimDirection);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	bool IsBarrelMoving();

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringStatus = EFiringState::Reloading;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000.0f; // 4000 m/s -> TODO: Find sensible value

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadSpeed = 3.0f; // in seconds

	double LastFireTime = -5.0;
	FVector AimDirection = FVector::ZeroVector;

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
};
