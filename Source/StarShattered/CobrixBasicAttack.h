// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AttackStrategy.h"
#include "CobrixBasicAttack.generated.h"

UCLASS()
class STARSHATTERED_API UCobrixBasicAttack : public UObject, public IAttackStrategy
{
	GENERATED_BODY()

public:
	virtual void ExecuteAttack(AActor* Target) override;
};