// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"


class UTankTracks;

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
		
public:

	UFUNCTION(BlueprintCallable, Category = "Input")
		void IntendMoveForward(float Throw);
	
	UFUNCTION(BluePrintCallable, Category = "Input")
		void IntendTurnRight(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTankTracks* LeftTrackToSet, UTankTracks* RightTrackToSet);

private:

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UTankTracks * LeftTrack = nullptr;
	UTankTracks * RightTrack = nullptr;
	
};
