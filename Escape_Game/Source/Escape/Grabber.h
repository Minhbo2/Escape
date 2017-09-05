// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	float Reach = 100.0f;
	
	UPhysicsHandleComponent* PhysicsHandler = nullptr;
	UInputComponent* InputComp              = nullptr;

	void FindPhysicsHandleComp();
	void FindInputComp();
	void Grab();
	void Release();
	FVector GetReachLineEnd();
	FVector GetReachLineStart();
	const FHitResult GetFirstPhysicsBodyInReach();
};
