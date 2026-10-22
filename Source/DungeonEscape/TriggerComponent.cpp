// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();


	UE_LOG(LogTemp, Display, TEXT("UTriggerComponent begin"));
	if (!IsPressurePlate)
		return;

	OnComponentBeginOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapBegin);		// set up a notification for when this component overlaps something
	OnComponentEndOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapEnd);		// set up a notification for when this component overlaps something

	if (MoverActor) 
	{
		Mover = MoverActor->FindComponentByClass<UMover>();
	}
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UTriggerComponent::SetTrigger(bool isTrigger)
{
	IsTriggered = isTrigger;
	if (Mover)
	{
		Mover->ShouldMove = IsTriggered;
	}
}

void UTriggerComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("PressureActivator")) 
	{
		NumberOfOverlaps++;
		SetTrigger(true);
	}

}

void UTriggerComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->ActorHasTag("PressureActivator")) 
	{
		NumberOfOverlaps--;
		if (NumberOfOverlaps == 0)
		{
			SetTrigger(false);
		}
	}

}
