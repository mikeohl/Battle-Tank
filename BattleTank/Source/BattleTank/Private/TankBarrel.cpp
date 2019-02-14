// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Move barrel appropriate distance in frame
	auto ElevationChange = FMath::Clamp<float>(RelativeSpeed, -1.5F, 1.5F) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds; // TODO: Create variable for 1.5F magic number
	auto RawNewElevation = FMath::Clamp<float>(RelativeRotation.Pitch + ElevationChange, MinDegreesElevation, MaxDegreesElevation);

	SetRelativeRotation(FRotator(RawNewElevation, 0.0F, 0.0F));
}


