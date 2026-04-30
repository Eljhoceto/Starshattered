// Fill out your copyright notice in the Description page of Project Settings.
#include "IdleState.h"
#include "StarshatteredAIController.h"
#include "MoveState.h"

void UIdleState::EnterState(AStarshatteredAIController* AIController)
{
	UE_LOG(LogTemp, Log, TEXT("Entrando a estado: IDLE"));
}

void UIdleState::UpdateState(AStarshatteredAIController* AIController, float DeltaTime)
{
	if (AIController->GetPlayerTarget() && AIController->GetPawn())
	{
		float Distance = FVector::Dist(AIController->GetPawn()->GetActorLocation(), AIController->GetPlayerTarget()->GetActorLocation());

		if (Distance < 1500.0f)
		{
			// ¡Actualizado al nuevo nombre de la función!
			AIController->SetEnemyState(NewObject<UMoveState>(AIController));
		}
	}
}