// Copyright Michael Ohl 2018-2019

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward speed, and +1 is max upward speed
	void Elevate(float RelativeSpeed);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreesPerSecond = 10; // Sensible default
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreesElevation = 40; // Sensible default
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinDegreesElevation = 0; // Sensible default

};
