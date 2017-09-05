// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"
#include "Gameframework/Pawn.h"
#include "Gameframework/PlayerController.h"
#include "Components/PrimitiveComponent.h"

#define OUT

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

	Owner      = GetOwner();
	//ActorOpens = GetWorld()->GetFirstPlayerController()->GetPawn(); // Set the actoropen to the playercontroller
}

void UOpenDoor::OpenDoor()
{
	// FRotator is a struct containing value for rotation(Pitch(Y), Yaw(Z), Roll(X))
	//Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
	OnOpen.Broadcast(); // This event is now can be creatable in blueprint
}



void UOpenDoor::CloseDoor()
{
	// FRotator is a struct containing value for rotation(Pitch(Y), Yaw(Z), Roll(X))
	//Owner->SetActorRotation(FRotator(0.0f, 90.0f, 0.0f));
	OnClose.Broadcast();
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.0f;

	// create an array of actor pointers
	TArray<AActor*> OverlappingActors;

	if (!PressurePlate) { return TotalMass; } // this will return 0
	// Get all overlapping actors with pressureplate
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (const auto& Actor : OverlappingActors) // much similar to the foreach
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass(); // mass is part of UPrimitiveComponent

	return TotalMass;
}




// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/*
	if (PressurePlate->IsOverlappingActor(ActorOpens)) // open the door base on the actor overlapping with the trigger volume
	{
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
		OpenDoor();
	}

	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
		CloseDoor();
	*/


	// Open door base on mass
	if (GetTotalMassOfActorsOnPlate() > TriggerMass)
	{
		//LastDoorOpenTime = GetWorld()->GetTimeSeconds(); // dont need this anymore
		OpenDoor();
	}
	else
		CloseDoor();
}
