// Fill out your copyright notice in the Description page of Project Settings.
#include "TankPlayerController.h"
#include "BattleTank.h"



void ATankPlayerController_Cpp::BeginPlay() {
	auto ControlledTank = GetControlledTank();
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController BeginPlay"));
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Not possesing a tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Possesing %s"), *ControlledTank->GetName());
	}
}


void ATankPlayerController_Cpp::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	AimTowardsCrossHair();
}



ATank* ATankPlayerController_Cpp::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController_Cpp::AimTowardsCrossHair() {
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // OUT parameter
	if (GetSightRayHitLocation(HitLocation)) {

		UE_LOG(LogTemp, Warning, TEXT("HitLocation : %s"), *HitLocation.ToString());

	}
}


bool ATankPlayerController_Cpp::GetSightRayHitLocation(FVector& HitLocation) const {
	int32 ViewPortSizeX, ViewportSizeY;
	GetViewportSize(ViewPortSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewPortSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	return true;
}
	
bool ATankPlayerController_Cpp::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LineTraceRange;
	
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
	return false;
}

bool ATankPlayerController_Cpp::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection)const {
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(
	    ScreenLocation.X,
		ScreenLocation.Y, 
		CameraWorldLocation, 
		LookDirection
	);


}
	