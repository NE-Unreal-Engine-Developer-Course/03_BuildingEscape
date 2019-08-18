// Copyright NE 2019

#include "Grabber.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "Math/Color.h"
#include "Engine/EngineTypes.h"
#include "Math/TwoVectors.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/PrimitiveComponent.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();		// IDE UActorComponent do stuff in the engine (inherited from UActor.)
	FindPhysicsHandleComponent();
	SetupInputComponent();
}

void UGrabber::FindPhysicsHandleComponent()
{	
	// Find for attached PhysicsHandle in Owner and assing a pointer to it.
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr) 
	{
		UE_LOG(LogTemp,Error,TEXT("%s missing PhysicsHandleComponent"), *GetOwner()->GetName())
	}
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{	
		InputComponent->BindAction("Grab", IE_Pressed,this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released,this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("%s missing InputComponent."), *GetOwner()->GetName())
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If the physics handle is attached
	if (!PhysicsHandle) {return;}
	if (PhysicsHandle->GrabbedComponent)
	{
		// move the object that we're holdig
		PhysicsHandle->SetTargetLocation(GetReachLinePointLocations().v2);
	}		
}

void UGrabber::Grab()
{
	// Line trace and see if it reaches any actor (static mesh comp.) with physics body collision channel set
	auto HitResult = GetFirstPhysicsBodyInReach(); 		// FHitResult HitResult = ...
	auto ComponentToGrab = HitResult.GetComponent(); 	// UPrimitiveComponent* ComponentToGrab = ...
	auto ActorHit = HitResult.GetActor(); 				// AActor* ActorHit = ...

	// If we hit something then attached physics handle
	if (ActorHit) 
	{		
		if (!PhysicsHandle) {return;}
		// Attach physics handle
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			ComponentToGrab, 
			NAME_None, // No bone needed
			ComponentToGrab->GetOwner()->GetActorLocation(),
			ComponentToGrab->GetOwner()->GetActorRotation()
		);
	}
}

void UGrabber::Release()
{
	if (!PhysicsHandle) {return;}
	PhysicsHandle->ReleaseComponent();
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{	
	// Line-trace (aso know as Ray-cast) out-to-reach disntance (cacl. distant of nearest object)
	FHitResult HitResult;
	FCollisionQueryParams TraceParameter(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult, 
		GetReachLinePointLocations().v1, // Start
		GetReachLinePointLocations().v2, // End
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameter
	);
	return HitResult;
}

FTwoVectors UGrabber::GetReachLinePointLocations() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation);

	FVector EndPointLocation =  PlayerViewPointLocation + Reach*PlayerViewPointRotation.Vector();
	return FTwoVectors(PlayerViewPointLocation, EndPointLocation);
}