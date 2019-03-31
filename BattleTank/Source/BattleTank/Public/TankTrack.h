// Copyright Michael Ohl 2018-2019

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"


/**
 * Tank Track Class sets maximum driving force and can apply force for tank movement
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	UTankTrack();

	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);
	
	// Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly)
	float MaxTrackForce = 40000000.0f; // Assume 40000 kg tank, 10 m/s^2 acceleration

protected:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

private:	  
	void ApplyCorrectiveForce();
	void Drive(float CurrentThrottle);
	void Drive_C(float CurrentThrottle);

	void GetWheels();
	TArray<class ASprungWheel*> GetWheels_C() const;

	TArray<class ASprungWheel*> Wheels;
};
