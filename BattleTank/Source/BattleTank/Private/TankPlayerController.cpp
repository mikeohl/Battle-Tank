// Copyright Michael Ohl 2018-2019

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

#include "Runtime/Engine/Classes/Engine/World.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ensure(ControlledTank))
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Controlling A Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Possessing: %s"), *(ControlledTank->GetName()));
		// *(... for T *char in macro
	}
	

	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController: Can't Find Aiming Component"));
	}
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimAtCrosshair() const
{
	auto ControlledTank = GetControlledTank();
	if (!ensure(ControlledTank)) { return; }
	
	FVector HitLocation; // Out Parameter
	if (GetSightRayHitLocation(HitLocation)) 
	{
		//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());
		ControlledTank->AimAt(HitLocation);

	}
	
}

// Get the world location that the crosshair is pointing at.
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, 
									ViewportSizeY * CrossHairYLocation
						  );

	FVector OutCameraWorldLocation;
	FVector OutCameraWorldDirection;
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, OutCameraWorldLocation, OutCameraWorldDirection))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Camera World Direction: %s"), *OutCameraWorldDirection.ToString());
		if (GetLookVectorHitLocation(OutCameraWorldDirection, OutHitLocation))
		{
			//Return location through out parameter
			return true;
		}
	}
	return false;
	
}

// Placeholder incase of refactor
bool ATankPlayerController::GetLookDirection(const FVector2D& ScreenLocation, FVector& LookDirection) const
{
	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(const FVector& LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();

	//Generate line to crosshair...
	auto EndLocation = StartLocation + LookDirection * LineTraceRange;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	return false;
}

//bool ATankPlayerController::GetViewportSize(int32 OutViewportSizeX, int32 OutViewportSizeY)
//{
//	return true;
//}