// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AActor* Actor = GetAcceptableActor();
	if(Actor != nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("Overlaping %s"),  *Actor->GetActorNameOrLabel());
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
		if(Component != nullptr)
		{
			Component->SetSimulatePhysics(false);
		}
		Actor->AttachToComponent(this,FAttachmentTransformRules::KeepWorldTransform);
		Mover->SetShouldMove(true);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Overlaping none"));
		Mover->SetShouldMove(false);
	}
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
}

AActor*  UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for(AActor* Actor : Actors)
	{
		if(Actor->ActorHasTag(AcceptableTag) && !Actor->ActorHasTag("Grabbed"))
		{
			return Actor;
		}
	}
	return nullptr;
}
