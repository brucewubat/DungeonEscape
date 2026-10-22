// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMath.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	// ...

	StartLocation = GetOwner()->GetActorLocation();
	TargetLocation = StartLocation + MoveOffset;
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (ShouldMove) 
	{
		TargetLocation = StartLocation + MoveOffset;
	}
	else 
	{
		TargetLocation = StartLocation;
	}

	AActor* Owner = GetOwner();
	FVector curLocation = Owner->GetActorLocation();
	float moveSpeed = MoveOffset.Length() / MoveTime;

	if (!curLocation.Equals(TargetLocation)) 
	{
		FVector newLocation = FMath::VInterpConstantTo(curLocation, TargetLocation, DeltaTime, moveSpeed);
		GetOwner()->SetActorLocation(newLocation);
	}

}

