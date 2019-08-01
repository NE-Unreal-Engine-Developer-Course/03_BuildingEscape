// Copyright NE 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:	
	 // Called when the game starts
	virtual void BeginPlay() override;
	// Called every frame
	void OpenDoor();
	void CloseDoor(); 

public:		
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	// Properties of clas that we can access via UE editor, details tab
	UPROPERTY(EditAnywhere)
	float OpenAngle = 270.0f;
		
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;
	
	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 0.5f; 


	// Find the owning actor of this ActorComponent (h-file)
	AActor *Owner;

	AActor* ActorThatOpens; // Pawn inherits from (is a) actor, NOT seletable in editor anymore.
	
	float LastDoorOpenTime;
	float TimePlay;
	
};
