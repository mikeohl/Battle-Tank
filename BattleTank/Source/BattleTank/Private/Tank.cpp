// Copyright Michael Ohl 2018-2019

#include "Tank.h"
#include "TankAIController.h"
#include "Runtime/Engine/Classes/Engine/World.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = InitialHealth;
}

// Apply damage to tank with maximum damage no greater than health remaining
float ATank::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	DamagePoints = FMath::Clamp<int32>(DamagePoints, 0, CurrentHealth);
	CurrentHealth -= DamagePoints;

	if (CurrentHealth <= 0)
	{
		OnTankDeath.Broadcast();
	}

	return (float)DamagePoints;
}

float ATank::GetHealthPercentage() const
{
	return (float)CurrentHealth / InitialHealth;
}

// Called to bind functionality to input
//void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//}

