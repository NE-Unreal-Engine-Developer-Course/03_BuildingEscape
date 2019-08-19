// Copyright NE 2019


#include "OpenDoor.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();

	if(!PressurePlate)
	{
		UE_LOG(LogTemp,Error,TEXT("%s missing PressurePlate."), *GetOwner()->GetName())
	}

}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// Get time in game
	TimePlay = GetWorld()->GetTimeSeconds();

	// Actor that opens is for now defined in h-file under private and set in UE editor.
	if (GetTotalMassOfActorsOnPlate() >30.f)
	{
		OpenDoor();
		// register last time actor overlapped.
		LastDoorOpenTime = GetWorld()->GetTimeSeconds(); 
	}

	
	// Check if is time to close the door.	
	if (TimePlay >= (LastDoorOpenTime + DoorCloseDelay))
	{
		CloseDoor();
	}
	
}



// methods that opens and closes the door
void UOpenDoor::OpenDoor()
{
	// Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
	OnOpenRequest.Broadcast();
}
void UOpenDoor::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;

	if (!PressurePlate) {return TotalMass;}
	PressurePlate->GetOverlappingActors(
		OUT OverlappingActors
		);

	for (const auto* Actor : OverlappingActors)
	{
		//if(!Actor){return TotalMass;}
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp,Warning,TEXT("%s on pressure plate"), *Actor->GetName())	
	}


	return TotalMass;
}