// Copyright Michael Ohl 2018-2019

#include "SpawnPoint.h"
#include "SprungWheel.h"
#include "Runtime/Engine/Classes/Engine/World.h"


// Sets default values for this component's properties
USpawnPoint::USpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnClassBlueprint, GetComponentTransform());
	if (!SpawnedActor) { return; }

	SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);

	SpawnedActor->FinishSpawning(GetComponentTransform());
}

AActor* USpawnPoint::GetSpawnedActor() const
{
	return SpawnedActor;
}


// Called every frame
void USpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

