// Copyright NE 2019


#include "OpenDoor.h"
#include "Gameframework/Actor.h"


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
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Actor that opens is for now defined in h-file under private and set in UE editor.
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
	}
}



// opens the door
void UOpenDoor::OpenDoor()
{
	AActor *Owner = GetOwner();
	FString ObjectName = Owner->GetName(); 
	
	// FQuat NewRotation = {0.0f, 0.0f, 300.0f, 0.0f}; 
	FRotator NewRotation = FRotator(0.0f, 300.0f, 0.0f); 
	Owner->SetActorRotation(NewRotation);

	// Print new rotation in UE console
	FString ObjectRotation = Owner->GetTransform().GetRotation().ToString(); 
	UE_LOG(LogTemp, Warning, TEXT("%s rotation is %s."),*ObjectName, *ObjectRotation);

}