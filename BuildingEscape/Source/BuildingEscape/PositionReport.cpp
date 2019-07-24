// Fill out your copyright notice in the Description page of Project Settings.


#include "PositionReport.h"
#include "Gameframework/Actor.h"

// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	// bWantsBeginPlay = true; in VIDEO, L66, 9:42. not in new UE4.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	// Super::___ means "do whatever happens in the thing I inherited it from (upstream), let it happen"
	Super::BeginPlay(); 

	// new code 

	// Return the name as Fstring of the Actor being pointed at.
	FString ObjectName = GetOwner()->GetName(); 
	
	FString ObjectPos = GetOwner()->GetTransform().GetLocation().ToString();
	//FString ObjectPos = GetOwner()>GetActorLocation().ToString();
	
	// UE_LOG is expecting a TCHAR array, and the * (ov.op.) effectively converts the FString to this type.
	UE_LOG(LogTemp, Warning, TEXT("%s loctated at %s."),*ObjectName, *ObjectPos);


/*  NOTE:
	 %s strings are wanted as TCHAR* by Log, so use *FString()
	//"MyCharacter's Name is %s"
	UE_LOG(YourLog,Warning,TEXT("MyCharacter's Name is %s"), *MyCharacter->GetName() );
*/

}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// Super::___ means "do whatever happens in the thing I inherited it from (upstream), let it happen"
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

