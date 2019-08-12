// Copyright NE 2019

#include "Grabber.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "Math/Color.h"
#include "Engine/EngineTypes.h"
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


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get player view point every tick	
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation);
	
	// Draw a red trace in the world to visualise
	FVector LineTraceEnd = PlayerViewPointLocation + Reach*PlayerViewPointRotation.Vector();

	// If the physics handle is attached
	if (PhysicsHandle->GrabbedComponent)
	{
		// move the object that we're holdig
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}	

	
}

void UGrabber::FindPhysicsHandleComponent()
{
	// Look for attached PhysicsHandle in Owner
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		// Do nothing if works
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("%s missing PhysicsHandleComponent"), *GetOwner()->GetName())
	}
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{	
		UE_LOG(LogTemp,Warning,TEXT("%s found InputComponent."), *GetOwner()->GetName())
		InputComponent->BindAction("Grab", IE_Pressed,this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released,this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("%s missing InputComponent."), *GetOwner()->GetName())
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp,Warning,TEXT("Grab key pressed"))

	// Line trace and see if it reaches any actor with physics body collision channel set
	auto HitResult = GetFirstPhysicsBodyInReach(); 		// FHitResult HitResult = ...
	auto ComponentToGrab = HitResult.GetComponent(); 	// UPrimitiveComponent* ComponentToGrab = ...
	auto ActorHit = HitResult.GetActor(); 				// AActor* ActorHit = ...

	// If we hit something then attached physics handle
	if (ActorHit) 
	{		
		// TODO attach physics handle
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			ComponentToGrab, 
			NAME_None, 
			ComponentToGrab->GetOwner()->GetActorLocation(),
			ComponentToGrab->GetOwner()->GetActorRotation()
			);

	}

}

void UGrabber::Release()
{
	UE_LOG(LogTemp,Warning,TEXT("Release key pressed"))

	// TODO release physics handle
	PhysicsHandle->ReleaseComponent();

}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	// Get player view point every tick	
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation);
	
	// Draw a red trace in the world to visualise
	FVector LineTraceEnd = PlayerViewPointLocation + Reach*PlayerViewPointRotation.Vector();
		
	// Line-trace (aso know as Ray-cast) out-to-reach disntance (cacl. distant of nearest object)
	FHitResult Hit;
	FCollisionQueryParams TraceParameter(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit, 
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameter
		);

	// Log what we hit.
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit %s."),*(ActorHit->GetName()))
	}
	return Hit;
}