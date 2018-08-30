// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

UCLASS()
class BATTLETANK_API ATankPlayerController_Cpp : public APlayerController {
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	ATank * GetControlledTank() const;

	void AimTowardsCrossHair();
	
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	UPROPERTY(EditAnywhere)
		float CrossHairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
		float CrossHairYLocation = 0.5;

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 10000;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
		
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection)const;


};
