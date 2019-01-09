// Fill out your copyright notice in the Description page of Project Settings.
#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "BattleTank.h"
#include "Engine/World.h"


void ATankPlayerController_Cpp::BeginPlay() {
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent)) { return; }
		FoundAimingComponent(AimingComponent);
}


void ATankPlayerController_Cpp::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	AimTowardsCrossHair();
}

void ATankPlayerController_Cpp::AimTowardsCrossHair() {
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent)) { return; }
	
	FVector HitLocation; // OUT parameter
	if (GetSightRayHitLocation(HitLocation)) {
		AimingComponent->AimAt(HitLocation);
	}
}


bool ATankPlayerController_Cpp::GetSightRayHitLocation(FVector& HitLocation) const {
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along that LookDirection, and see what we hit (up to max range)
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	return true;
}
	
bool ATankPlayerController_Cpp::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false; // Line trace didn't succeed
}

bool ATankPlayerController_Cpp::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection)const {
	FVector CameraWorldLocation; // To be discarded
	return  DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
}
	