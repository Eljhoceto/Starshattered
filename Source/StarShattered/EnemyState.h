// Fill out your copyright notice in the Description page of Project Settings.
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyState.generated.h"

UINTERFACE(MinimalAPI)
class UEnemyState : public UInterface
{
	GENERATED_BODY()
};

class STARSHATTERED_API IEnemyState
{
	GENERATED_BODY()

public:
	virtual void EnterState(class AStarshatteredAIController* AIController) = 0;
	virtual void UpdateState(class AStarshatteredAIController* AIController, float DeltaTime) = 0;
};