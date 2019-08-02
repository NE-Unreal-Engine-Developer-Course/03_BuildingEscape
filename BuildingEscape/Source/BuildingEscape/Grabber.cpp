// Copyright NE 2019

#include "Grabber.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "Math/Color.h"

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
	
	
	// UE_LOG(LogTemp, Warning, TEXT("Player View Point: Location.: %s; Rotation.: %s."),
	// *PlayerViewPointLocation.ToString(), 
	// *PlayerViewPointRotation.ToString()
	// )

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
	
	
	// Ray-cast out-to-reach disntance (cacl. distant of nearest object)
	// See what we hit.

}

