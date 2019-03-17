// Copyright Michael Ohl 2018-2019

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

// Forward Declaration
class ATank;


/**
 * Initializes and directs AI tank behavior
 * Depends on TankMovementComponent via pathfinding system
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

protected:
	UPROPERTY(EditDefaultsOnly)
	float AcceptanceRadius = 1000.0f;
};
