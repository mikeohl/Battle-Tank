// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Move(float Intensity)
{
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s throttle set to %f"), *Name, Intensity);

	//if (!LeftTrack || !RightTrack)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Track(s) missing from tank"));
	//	return;
	//}

	//RightTrack->SetThrottle(Intensity);
	//LeftTrack->SetThrottle(Intensity);
}
/*
void UTankMovementComponent::SetLeftTrackReference(UTankTrack* LeftTrackToSet)
{
	if (!LeftTrackToSet) { return; }
	//LeftTrack = LeftTrackToSet;
}

void UTankMovementComponent::SetRightTrackReference(UTankTrack* RigthTrackToSet)
{
	if (!RigthTrackToSet) { return; }
	//RightTrack = RigthTrackToSet;
}*/