// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackState.h"
#include "StarshatteredAIController.h"
#include "IdleState.h"

void UAttackState::EnterState(AStarshatteredAIController* AIController)
{
	UE_LOG(LogTemp, Log, TEXT("Entrando a estado: ATTACK"));
}

void UAttackState::UpdateState(AStarshatteredAIController* AIController, float DeltaTime)
{
	AIController->PerformAttack();

	// ¡Actualizado al nuevo nombre de la función!
	AIController->SetEnemyState(NewObject<UIdleState>(AIController));
}

