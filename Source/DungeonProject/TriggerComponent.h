// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mover.h"
#include "Components/BoxComponent.h"
#include "TriggerComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )        
class DUNGEONPROJECT_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()
public:	                                                                                                                        
	UTriggerComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	void SetMover(UMover* NewMover);
	UPROPERTY(EditAnywhere)
	FName AcceptableTag;
protected:                                   
	// Called when the game starts           
	virtual void BeginPlay() override;
	AActor* GetAcceptableActor() const;
	UMover* Mover;
};
