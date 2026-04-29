#include "StarshatteredAIController.h"
#include "Kismet/GameplayStatics.h"
#include "IdleState.h"
#include "CobrixBasicAttack.h"

AStarshatteredAIController::AStarshatteredAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AStarshatteredAIController::BeginPlay()
{
	Super::BeginPlay();

	PlayerTarget = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	AttackStrategyObj = NewObject<UCobrixBasicAttack>(this);
	AttackStrategy = Cast<IAttackStrategy>(AttackStrategyObj);

	// Usamos el nuevo nombre de la función
	SetEnemyState(NewObject<UIdleState>(this));
}

void AStarshatteredAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentState)
	{
		CurrentState->UpdateState(this, DeltaTime);
	}
}

// Implementación con el nuevo nombre
void AStarshatteredAIController::SetEnemyState(UObject* NewStateObject)
{
	if (NewStateObject && NewStateObject->Implements<UEnemyState>())
	{
		CurrentStateObj = NewStateObject;
		CurrentState = Cast<IEnemyState>(NewStateObject);

		if (CurrentState)
		{
			CurrentState->EnterState(this);
		}
	}
}

void AStarshatteredAIController::PerformAttack()
{
	if (AttackStrategy && PlayerTarget)
	{
		AttackStrategy->ExecuteAttack(PlayerTarget);
	}
}
