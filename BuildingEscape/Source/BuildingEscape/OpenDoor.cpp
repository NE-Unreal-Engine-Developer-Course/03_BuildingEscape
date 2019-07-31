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

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

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
	// Find the owning actor of this ActorComponent (h-file)
	AActor *Owner = GetOwner();
	FString ObjectName = Owner->GetName(); 
	
	// Define new rotating vector as FQuat NewRotation = {0.0f, 0.0f, 300.0f, 0.0f}: , or as
	FRotator NewRotation = FRotator(0.0f, 300.0f, 0.0f); 
	
	// Set new rotation vector into owner.
	Owner->SetActorRotation(NewRotation);

	// Print new rotation in UE console
	FString ObjectRotation = Owner->GetTransform().GetRotation().ToString(); 
	UE_LOG(LogTemp, Warning, TEXT("%s rotation is %s."),*ObjectName, *ObjectRotation);

}