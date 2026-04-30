// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveState.h"
#include "StarshatteredAIController.h"
#include "AttackState.h"

void UMoveState::EnterState(AStarshatteredAIController* AIController)
{
	UE_LOG(LogTemp, Log, TEXT("Entrando a estado: MOVE"));
}

void UMoveState::UpdateState(AStarshatteredAIController* AIController, float DeltaTime)
{
	if (AIController->GetPlayerTarget() && AIController->GetPawn())
	{
		AIController->MoveToActor(AIController->GetPlayerTarget(), 100.0f);

		float Distance = FVector::Dist(AIController->GetPawn()->GetActorLocation(), AIController->GetPlayerTarget()->GetActorLocation());

		if (Distance <= 500.0f)
		{
			// ¡Actualizado al nuevo nombre de la función!
			AIController->SetEnemyState(NewObject<UAttackState>(AIController));
		}
	}
}
