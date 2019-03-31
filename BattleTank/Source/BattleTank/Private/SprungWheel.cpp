// Copyright Michael Ohl 2018-2019

#include "SprungWheel.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Components/SphereComponent.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	//Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring"));
	Spring2 = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring2"));
	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	WheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("WheelConstraint"));
	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	//Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
	

	SetRootComponent(Spring2);
	//Mass->SetupAttachment(RootComponent);
	Axle->SetupAttachment(RootComponent);
	WheelConstraint->SetupAttachment(Axle);
	Wheel->SetupAttachment(Axle);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);
	
	SetupConstraints();
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->TickGroup == TG_PostPhysics)
	{
		CurrentDrivingForce = 0.0f;
	}
}

// Constrain wheel to parent body
void ASprungWheel::SetupConstraints()
{
	if (!GetAttachParentActor()) { return; }
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) { return; }
	Spring2->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
	WheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	CurrentDrivingForce += ForceMagnitude;
	//if (!(ensure(Wheel) && ensure(Axle))) { return; }
	//Wheel->AddForce(Axle->GetForwardVector() * ForceMagnitude);
}

void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!(ensure(Wheel) && ensure(Axle))) { return; }
	Wheel->AddForce(Axle->GetForwardVector() * CurrentDrivingForce);
}
