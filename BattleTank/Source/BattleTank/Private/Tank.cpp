// Copyright Michael Ohl 2018-2019

#include "Tank.h"
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
}

// Apply damage to tank with maximum damage no greater than health remaining
float ATank::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("DamageAmount = %f"), DamageAmount);
	
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	DamagePoints = FMath::Clamp<int32>(DamagePoints, 0, CurrentHealth);
	UE_LOG(LogTemp, Warning, TEXT("DamageToApply = %i"), DamagePoints);
	
	CurrentHealth -= DamagePoints;

	UE_LOG(LogTemp, Warning, TEXT("DamageApplied = %i, Health Remaining = %i"), DamagePoints, CurrentHealth);

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

