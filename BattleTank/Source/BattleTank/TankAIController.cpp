// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "TankAIController.h"
#include "Tank.h"
#include "AIController.h"
#include "Engine/World.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn()); 
	auto ControlledTank = Cast<ATank>(GetPawn());

	Super::Tick(DeltaTime);
	if (PlayerTank)
	{
	
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		ControlledTank->Fire();
	}
}



