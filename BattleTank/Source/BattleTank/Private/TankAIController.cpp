// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
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
	if (PlayerPawn)
	{
		PlayerTank = Cast<ATank>(PlayerPawn);
	}

	// Set this tank
	ThisTank = Cast<ATank>(GetPawn());

	if (!PlayerTank || !ThisTank)
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
	
	if (PlayerTank && ThisTank)
	{
		MoveToActor(PlayerTank, AcceptanceRadius);

		// Aim at player
		ThisTank->AimAt(PlayerTank->GetActorLocation());

		// Fire if ready
		ThisTank->Fire();
	}

}

