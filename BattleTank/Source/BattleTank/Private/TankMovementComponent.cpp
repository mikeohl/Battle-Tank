// Copyright Michael Ohl 2018-2019


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

	if (!ensure(LeftTrack && RightTrack))
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

	if (!ensure(LeftTrack && RightTrack))
	{
		UE_LOG(LogTemp, Warning, TEXT("Track(s) missing from tank"));
		return;
	}

	RightTrack->SetThrottle(-Intensity);
	LeftTrack->SetThrottle(Intensity);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	UE_LOG(LogTemp, Warning, TEXT("%s: RequestDirectMove Called"), *GetOwner()->GetName())

	auto TankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIMoveIntention = MoveVelocity.GetSafeNormal();

	auto MoveIntensity = FVector::DotProduct(AIMoveIntention, TankForwardDirection);
	auto TurnIntensity = FVector::CrossProduct(TankForwardDirection, AIMoveIntention).Z;
	UE_LOG(LogTemp, Warning, TEXT("%s: Move Intensity = %f, Turn Intensity = %f"), *GetOwner()->GetName(), MoveIntensity, TurnIntensity);

	Move(MoveIntensity);
	Turn(TurnIntensity);
	//UE_LOG(LogTemp, Warning, TEXT("RequestDirectMove Called"));
}
