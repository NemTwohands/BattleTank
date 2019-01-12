// Fill out your copyright notice in the Description page of Project Settings.


#pragma once
#include "AIController.h"
#include "TankAIController.generated.h"


UCLASS()
class BATTLETANK_API ATankAIController : public AAIController {
	GENERATED_BODY()

	virtual void BeginPlay() override;
private:

	virtual void Tick(float DeltaSeconds) override;

	float  AcceptanceRadius = 3000;

};
