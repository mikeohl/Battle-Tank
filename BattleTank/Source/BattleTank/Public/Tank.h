// Copyright Michael Ohl 2018-2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

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

public:	
	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser) override;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercentage() const;

	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FTankDelegate OnTankDeath;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 InitialHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth; // Initialized in BeginPlay
};
