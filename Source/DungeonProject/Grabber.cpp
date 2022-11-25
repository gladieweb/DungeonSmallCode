// Fill out your copyright notice in the Description page of Project Settings.
#include "Grabber.h"

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
	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if(PhysicsHandle == nullptr)
	{
		return;
	}
	if(PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
}

void UGrabber::Release()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if(PhysicsHandle == nullptr)
	{
		return;
	}

	if(PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		AActor* GrabbedActor = PhysicsHandle->GetGrabbedComponent() ->GetOwner();
		GrabbedActor->Tags.Remove("Grabbed");
		PhysicsHandle->ReleaseComponent();
	}
}

void UGrabber::Grab()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if(PhysicsHandle == nullptr)
	{
		return;
	}
	
	FHitResult HitResult;

	if(GetGrabbableInReach(HitResult))
	{
		AActor* HitActor = HitResult.GetActor();
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint,10,10,FColor::Red, false, 5);
		DrawDebugSphere(GetWorld(), HitResult.Location,10,10,FColor::Green, false, 5);

		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->SetSimulatePhysics(true);
		HitComponent->WakeAllRigidBodies();
		HitActor->Tags.Add("Grabbed");
		HitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
			);
		UE_LOG(LogTemp, Display, TEXT("hit %s"), *HitActor->GetActorNameOrLabel());
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("no actor hit"));
	}
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	return  GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}

bool UGrabber::GetGrabbableInReach(FHitResult& HitResult) const
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;
	
	DrawDebugLine(GetWorld(),Start ,End, FColor::Green);
	DrawDebugSphere(GetWorld(), End,10,10,FColor::Blue, false, 5);
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	return GetWorld()->SweepSingleByChannel(
		HitResult,
		Start,
		End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere
		);
}

