// Copyright Michael Ohl 2018-2019

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "Runtime/Engine/Classes/Engine/World.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	InitializeTanks();
}

void ATankAIController::InitializeTanks()
{
	// Set player tank
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (ensure(PlayerPawn))
	{
		PlayerTank = Cast<ATank>(PlayerPawn);
	}

	// Set this tank
	ThisTank = Cast<ATank>(GetPawn());

	if (!ensure(PlayerTank && ThisTank))
	{
		UE_LOG(LogTemp, Warning, TEXT("FAILED TO GET TANK"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController (%s) found player tank: %s"), *(ThisTank->GetName()), *(PlayerTank->GetName()));
	}
	UE_LOG(LogTemp, Warning, TEXT("AIController Begin Play"));
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// if (!PlayerTank || !ThisTank) { InitializeTanks(); }
	
	if (!ensure(PlayerTank && ThisTank)) { return; }

	MoveToActor(PlayerTank, AcceptanceRadius);
	
	// Aim at player
	auto AimingComponent = ThisTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
		
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	// Fire if ready
	AimingComponent->Fire(); 

}

