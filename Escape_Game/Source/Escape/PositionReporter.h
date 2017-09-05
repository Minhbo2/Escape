// Fill out your copyright notice in the Description page of Project Settings. Settings => Project Setting

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PositionReporter.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ESCAPE_API UPositionReporter : public UActorComponent
{
	GENERATED_BODY()

	public:	
		// Sets default values for this component's properties
		// Constructor
		UPositionReporter();

	protected:
		// Called when the game starts
		// will be override with the cpp file
		virtual void BeginPlay() override;

	public:	
		// Called every frame
		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
