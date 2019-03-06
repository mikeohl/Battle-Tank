// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

// Forward Declaration
class ATank;


/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void InitializeTanks();

private:
	ATank* ThisTank = nullptr;
	ATank* PlayerTank = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	float AcceptanceRadius = 3000.0f;
};
