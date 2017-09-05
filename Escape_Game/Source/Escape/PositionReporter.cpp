// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionReporter.h"
#include "Gameframework/Actor.h" // 4.16 and higher need this include


// Sets default values for this component's properties
UPositionReporter::UPositionReporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReporter::BeginPlay()
{
	Super::BeginPlay();

	FString ObjectName = GetOwner()->GetName();
	FString ObjectPos = GetOwner()->GetActorLocation().ToString(); // or longer way GetOwner()->GetTransform().GetLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("This is %s"), *ObjectName); // UE_LOG is expecting TChar array, * effectively converts the string to this type, only in this instance
	UE_LOG(LogTemp, Warning, TEXT("This position is %s"), *ObjectPos); 
}


// Called every frame
void UPositionReporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

