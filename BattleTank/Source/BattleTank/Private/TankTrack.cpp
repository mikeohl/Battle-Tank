// Copyright Michael Ohl 2018-2019


#include "TankTrack.h"
#include "Runtime/Engine/Classes/Engine/World.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	// Bind OnComponentHit if not bound
	if (!OnComponentHit.IsBound()) 
	{
		OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
	}
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	auto Name = GetOwner()->GetName();
	if (abs(AppliedThrottle) > .1f)
	UE_LOG(LogTemp, Warning, TEXT("%s Drive Throttle set to %f"), *Name, AppliedThrottle);
}

void UTankTrack::SetThrottle(float Throttle)
{
	AppliedThrottle = FMath::Clamp<float>(Throttle, -1.0f, 1.0f);
	auto Name = GetOwner()->GetName();

	auto ForceApplied = GetForwardVector() * AppliedThrottle * MaxTrackForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

	//if (abs(AppliedThrottle) > .5f)
	//UE_LOG(LogTemp, Warning, TEXT("%s: Stick Throttle: %f"), *Name, AppliedThrottle);
}

void UTankTrack::Drive()
{
	auto ForceApplied = GetForwardVector() * AppliedThrottle * MaxTrackForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

	auto Name = GetOwner()->GetName();
	//if (abs(AppliedThrottle) > .5f)
	//UE_LOG(LogTemp, Warning, TEXT("%s Drive Throttle set to %f"), *Name, AppliedThrottle);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//Drive();
	ApplyCorrectiveForce();

	//auto Name = GetOwner()->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s: On Hit, Throttle: %f"), *Name, AppliedThrottle);
}

void UTankTrack::ApplyCorrectiveForce()
{
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	// Calculate the slippage speed and necessary correction force
	auto HorizontalSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto CorrectiveForce = (-HorizontalSpeed / GetWorld()->GetDeltaSeconds() / 1.5f) * (TankRoot->GetMass() / 2) * GetRightVector();

	TankRoot->AddForce(CorrectiveForce);

	// Alternate use of force at location
	//auto ForceLocation = GetComponentLocation();
	//TankRoot->AddForceAtLocation(-Slide / DeltaTime * GetRightVector() * TankRoot->GetMass()/2, ForceLocation);
}