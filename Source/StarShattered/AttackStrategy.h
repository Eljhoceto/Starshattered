// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AttackStrategy.generated.h"

UINTERFACE(MinimalAPI)
class UAttackStrategy : public UInterface
{
	GENERATED_BODY()
};

class STARSHATTERED_API IAttackStrategy
{
	GENERATED_BODY()

public:
	virtual void ExecuteAttack(AActor* Target) = 0;
};