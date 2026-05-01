// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackState.h"
#include "StarshatteredAIController.h"
#include "IdleState.h"

void UAttackState::EnterState(AStarshatteredAIController* AIController)
{
	UE_LOG(LogTemp, Log, TEXT("Entrando a estado: ATTACK"));
	// Lo ponemos a 0 para que dispare casi de inmediato al entrar en rango por primera vez
	CooldownTimer = 0.0f;
}

void UAttackState::UpdateState(AStarshatteredAIController* AIController, float DeltaTime)
{
	if (!AIController) return;

	APawn* ControlledPawn = AIController->GetPawn();
	AActor* PlayerTarget = AIController->GetPlayerTarget();

	if (ControlledPawn && PlayerTarget)
	{
		// 1. Evalúa si el jugador está a menos de 800 unidades
		float DistanceToPlayer = FVector::Dist(ControlledPawn->GetActorLocation(), PlayerTarget->GetActorLocation());

		if (DistanceToPlayer <= AttackRange)
		{
			// 2. Gestionar el 'cooldown' de 2 segundos
			CooldownTimer -= DeltaTime;
			if (CooldownTimer <= 0.0f)
			{
				// Es válido: Llamamos a la estrategia
				AIController->PerformAttack();

				// Reiniciamos el cooldown
				CooldownTimer = AttackCooldown;
			}
		}
		else
		{
			// Si el jugador se aleja, volvemos a Idle (o a tu estado de persecución)
			AIController->SetEnemyState(NewObject<UIdleState>(AIController));
		}
	}
}

