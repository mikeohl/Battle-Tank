// Copyright Michael Ohl 2018-2019


#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{


	// TODO: Clamp the throttle
	auto ForceApplied = GetForwardVector() * Throttle * MaxTrackForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


