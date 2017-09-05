// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent); // make a new delegate class FOnOpenRequest

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

	private:
		UPROPERTY(EditAnywhere) // a Unreal property shows in component detail inspector, same as [SerializeField]
		ATriggerVolume* PressurePlate = nullptr; // empty variable for a trigger volume

		
		//UPROPERTY(EditAnywhere) // dont need this anymore, blueprint curve will handle this
		//	float DoorCloseDelay = 1.0f;


		// float LastDoorOpenTime; // same goes for this


		// AActor* ActorOpens = nullptr; // we can use APawn type to be more specific, but since we want other object(s) in the scene to able to open the door as well, we use AActor
			// AActor -> APawn -> ACharacter


		// AActor is an object type of AActor class
		AActor* Owner = nullptr;

		UPROPERTY(EditAnywhere)
		float TriggerMass = 30.0f;



	public:	
		// Sets default values for this component's properties
		UOpenDoor();

	protected:
		// Called when the game starts
		virtual void BeginPlay() override;

		void OpenDoor();
		void CloseDoor();
		float GetTotalMassOfActorsOnPlate();


	public:	
		// Called every frame
		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


		UPROPERTY(BlueprintAssignable) // make the delegate class blueprintassignable
		FDoorEvent OnOpen; // create event call OnOpenRequest for blueprint

		UPROPERTY(BlueprintAssignable)
		FDoorEvent OnClose;
};
