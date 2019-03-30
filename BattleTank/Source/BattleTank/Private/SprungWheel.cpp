// Copyright Michael Ohl 2018-2019

#include "SprungWheel.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring"));
	Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	
	SetRootComponent(Spring);
	Mass->SetupAttachment(RootComponent);
	Wheel->SetupAttachment(RootComponent);
	

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetAttachParentActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Null"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Null"))
	}

}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

