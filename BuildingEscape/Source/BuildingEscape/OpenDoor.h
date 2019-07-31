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

public:		
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	// Properties of clas that we can access via UE editor, details tab
	UPROPERTY(VisibleAnywhere)
	float OpenAngle = 75.0f;
		
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;
	
	AActor* ActorThatOpens; // Pawn inherits from (is a) actor, NOT seletable in editor anymore.
	
};
