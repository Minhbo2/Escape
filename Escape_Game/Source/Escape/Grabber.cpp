// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "Gameframework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "Components/PrimitiveComponent.h"

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
	FindPhysicsHandleComp();
	FindInputComp();
}






// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PhysicsHandler) { return; }

	if (PhysicsHandler->GrabbedComponent)
		PhysicsHandler->SetTargetLocation(GetReachLineEnd());
}



void UGrabber::FindPhysicsHandleComp()
{
	// Look for attached PhysicsHandle to this Actor
	PhysicsHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandler)
		UE_LOG(LogTemp, Error, TEXT("%s is missing physics component."), *GetOwner()->GetName());
}

void UGrabber::FindInputComp()
{
	InputComp = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComp)
	{
		InputComp->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab); // BindAction(Binding Name of Action in Project Setting -> Input, 
																		  // enum state of Action, class the function is in, Reference to the function)
		InputComp->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}




void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabbing action is working!"));

	auto HitResult = GetFirstPhysicsBodyInReach(); // get the first physic body object
	auto ComponentToGrab = HitResult.GetComponent(); // Get the component of that object happen to be a mesh
	auto ActorHit = HitResult.GetActor();

	if (ActorHit)
	{
		//attach physicshandle
		PhysicsHandler->GrabComponentAtLocationWithRotation(
			ComponentToGrab, //what to grab
			NAME_None, // name of the skeleton if there is one
			ComponentToGrab->GetOwner()->GetActorLocation(), // get component's owner location
			FRotator(0) // rotation
		);
	}
}


void UGrabber::Release()
{
	PhysicsHandler->ReleaseComponent();
}

FVector UGrabber::GetReachLineEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotator;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotator
	);

	return PlayerViewPointLocation + PlayerViewPointRotator.Vector() * Reach;
}

FVector UGrabber::GetReachLineStart()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotator;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotator
	);

	return PlayerViewPointLocation; 
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	/*
	DrawDebugLine(
		GetWorld(),
		GetReachLineStart(),
		GetReachLineEnd(),
		FColor(255, 0, 0),
		false, 0.0f,
		0.0f,
		10.0f
	);
	*/


	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner()); // params (tag of object, complex collision detection, ignore AActor)
	FHitResult HitResult;
	// RayCasting for object type
	GetWorld()->LineTraceSingleByObjectType( // params
		OUT HitResult, // store a hit result much like RayCastHit
		GetReachLineStart(), // origin
		GetReachLineEnd(), // direction/end of ray
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), // check for a physic body type on the Hit, if it s a Physic Body
		TraceParams // passing in additional params 
	);
	return HitResult;
}

