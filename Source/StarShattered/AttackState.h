// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EnemyState.h"
#include "AttackState.generated.h"

UCLASS()
class STARSHATTERED_API UAttackState : public UObject, public IEnemyState
{
	GENERATED_BODY()

public:
	virtual void EnterState(AStarshatteredAIController* AIController) override;
	virtual void UpdateState(AStarshatteredAIController* AIController, float DeltaTime) override;

private:
	// Variables para gestionar el disparo y la distancia
	float CooldownTimer = 0.0f;
	const float AttackCooldown = 2.0f;
	const float AttackRange = 800.0f;
};
