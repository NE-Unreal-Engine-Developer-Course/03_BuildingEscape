// Copyright NE 2019

#include "Grabber.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "Math/Color.h"
#include "Engine/EngineTypes.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));
	
	// Look for attached PhysicsHandle in Owner
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		// Do nothing if works
		UE_LOG(LogTemp,Warning,TEXT("%s present PhysicsHandleComponent "), *GetOwner()->GetName())
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("%s missing PhysicsHandleComponent"), *GetOwner()->GetName())
	}

	// Look for attached InputComponent in Owner (at runtime, not listed in UE->Details tab!)
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		// Do nothing if works
		UE_LOG(LogTemp,Warning,TEXT("%s present InputComponent"), *GetOwner()->GetName())
		InputComponent->BindAction("Grab", IE_Pressed,this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released,this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("%s missing InputComponent"), *GetOwner()->GetName())
	}

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
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(0,0,255), 
		false,
		0.f,
		0.f,
		5.f
	);
		
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
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp,Warning,TEXT("Grab key pressed"))

}

void UGrabber::Release()
{
	UE_LOG(LogTemp,Warning,TEXT("Release key pressed"))

}