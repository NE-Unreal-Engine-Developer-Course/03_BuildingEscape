// Copyright NE 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	
	float Reach = 100.f;
		
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* InputComponent = nullptr;
	
	// Ray-cast and grab what's in reach
	void Grab();

	// Called when grab key is released
	void Release();
	
	// Find (assumed) attached PhysicsHandleComponent
	void FindPhysicsHandleComponent();
	
	// Setup (assumed) attached InputComponent (at runtime, not listed in UE->Details tab!)
	void SetupInputComponent();

	// Return hir for first physics body in reach
	FHitResult GetFirstPhysicsBodyInReach() const;
	
	// Returns end of Reach line
	FTwoVectors GetReachLinePointLocations() const;

};
