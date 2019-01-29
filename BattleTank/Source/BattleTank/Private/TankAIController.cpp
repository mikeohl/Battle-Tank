// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();
	auto AITank = GetAIControlledTank();

	if (!PlayerTank || !AITank)
	{
		UE_LOG(LogTemp, Warning, TEXT("FAILED TO GET TANK"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController (%s) found player tank: %s"), *(AITank->GetName()), *(PlayerTank->GetName()));
	}
	UE_LOG(LogTemp, Warning, TEXT("AIController Begin Play"));

}

ATank* ATankAIController::GetAIControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank = GetPlayerTank();
	if (PlayerTank)
	{
		// TODO: Move toward player
		// Aim at player
		GetAIControlledTank()->AimAt(PlayerTank->GetActorLocation());
		// Fire if ready
	}
}

