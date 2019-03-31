// Copyright Michael Ohl 2018-2019


#include "TankTrack.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"
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

	// ...
}

void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1.0f, 1.0f);
	Drive(CurrentThrottle);

	//if (abs(CurrentThrottle) > .5f)
	//UE_LOG(LogTemp, Warning, TEXT("%s: Stick Throttle: %f"), *Name, CurrentThrottle);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//Drive();
	//ApplyCorrectiveForce();
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

void UTankTrack::GetWheels()
{
	if (Wheels.Num() > 0) { return; }
	
	TArray<USceneComponent*> SpawnPoints;
	GetChildrenComponents(false, SpawnPoints);

	for (USceneComponent* SpawnPoint : SpawnPoints)
	{
		auto Point = Cast<USpawnPoint>(SpawnPoint);
		if (!Point) { continue; }
		auto Actor = Point->GetSpawnedActor();
		auto Wheel = Cast<ASprungWheel>(Actor);
		if (!Wheel) { continue; }
		Wheels.Add(Wheel);
	}
}

void UTankTrack::Drive(float CurrentThrottle)
{
	GetWheels();

	auto ForceApplied = CurrentThrottle * MaxTrackForce;
	auto ForcePerWheel = ForceApplied / Wheels.Num();

	for (ASprungWheel* Wheel : Wheels)
	{
		if (!ensure(Wheel)) { return; }
		Wheel->AddDrivingForce(ForcePerWheel);
	}

	//auto Name = GetOwner()->GetName();
	//if (abs(CurrentThrottle) > .5f)
	//UE_LOG(LogTemp, Warning, TEXT("%s Drive Throttle set to %f"), *Name, CurrentThrottle);
}


TArray<ASprungWheel*> UTankTrack::GetWheels_C() const
{
	TArray<ASprungWheel*> WheelArray;

	TArray<USceneComponent*> SpawnPoints;
	GetChildrenComponents(true, SpawnPoints);

	for (USceneComponent* SpawnPoint : SpawnPoints)
	{
		auto Point = Cast<USpawnPoint>(SpawnPoint);
		if (!Point) { continue; }
		auto Actor = Point->GetSpawnedActor();
		auto Wheel = Cast<ASprungWheel>(Actor);
		if (!Wheel) { continue; }
		WheelArray.Add(Wheel);
	}

	return WheelArray;
}

void UTankTrack::Drive_C(float CurrentThrottle)
{
	auto ForceApplied = CurrentThrottle * MaxTrackForce;
	auto Wheels_C = GetWheels_C();
	auto ForcePerWheel = ForceApplied / Wheels_C.Num();

	for (ASprungWheel* Wheel : Wheels_C)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}
