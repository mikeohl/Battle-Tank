// Copyright Michael Ohl 2018-2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

// Forward Declaration
class ATank;
class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank * GetControlledTank() const;
	void AimAtCrosshair() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimingComponent);

private:
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookDirection(const FVector2D& ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(const FVector& LookDirection, FVector& HitLocation) const;
	//bool GetViewportSize(int32 OutViewportSizeX, int32 OutViewportSizeY);

	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5f;
	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.33333f;
	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.0f;
};
