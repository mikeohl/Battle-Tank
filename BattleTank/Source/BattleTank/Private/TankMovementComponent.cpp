// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::InitializeTracks(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::Move(float Intensity)
{
	//auto Name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s throttle set to %f"), *Name, Intensity);

	if (!LeftTrack || !RightTrack)
	{
		UE_LOG(LogTemp, Warning, TEXT("Track(s) missing from tank"));
		return;
	}

	RightTrack->SetThrottle(Intensity);
	LeftTrack->SetThrottle(Intensity);
}

// TODO: Find a better way to mix intensities. Not a fan of this implementation
void UTankMovementComponent::Turn(float Intensity)
{
	//auto Name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s throttle set to %f"), *Name, Intensity);

	if (!LeftTrack || !RightTrack)
	{
		UE_LOG(LogTemp, Warning, TEXT("Track(s) missing from tank"));
		return;
	}

	RightTrack->SetThrottle(-Intensity);
	LeftTrack->SetThrottle(Intensity);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No Super - Replacement functionality
	auto TankName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s moving at velocity %s"), *TankName, *MoveVelocity.GetSafeNormal().ToString());
	//UE_LOG(LogTemp, Warning, TEXT("RequestDirectMove Called"));
}
