// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "TankAIController.h"
#include "AIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn(); 
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }
	
	MoveToActor(PlayerTank, AcceptanceRadius);
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

}



