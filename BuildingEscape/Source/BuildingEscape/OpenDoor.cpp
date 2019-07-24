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

	// ...
	//float Zaxis = GetOwner()->GetTransform().GetRotation().Z;

	AActor *Owner = GetOwner();
	FString ObjectName = Owner->GetName(); 
	
	// Read and write in console actual rotation of component.
	FString ObjectRotation = Owner->GetTransform().GetRotation().ToString(); 
	UE_LOG(LogTemp, Warning, TEXT("%s rotation is %s."),*ObjectName, *ObjectRotation);

	// setting up new rotation vector, values in deg, from 0 to 360
	FRotator NewRotation = FRotator(0.0f, 300.0f, 0.0f); 
	//FQuat NewRotation = {0.0f, 0.0f, 300.0f, 0.0f}; 
	Owner->SetActorRotation(NewRotation);

	// Read and write in console actual rotation of component.
	FString ObjectRotation1 = Owner->GetTransform().GetRotation().ToString(); 
	UE_LOG(LogTemp, Warning, TEXT("%s rotation is %s."),*ObjectName, *ObjectRotation1);
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

