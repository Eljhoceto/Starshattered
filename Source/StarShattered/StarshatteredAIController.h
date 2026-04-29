#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyState.h"
#include "AttackStrategy.h"
#include "StarshatteredAIController.generated.h"

UCLASS()
class STARSHATTERED_API AStarshatteredAIController : public AAIController
{
	GENERATED_BODY()

public:
	AStarshatteredAIController();
	virtual void Tick(float DeltaTime) override;

	// RENOMBRADO: Cambiamos ChangeState a SetEnemyState para no chocar con AController
	void SetEnemyState(UObject* NewStateObject);
	void PerformAttack();

	AActor* GetPlayerTarget() const { return PlayerTarget; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UObject* CurrentStateObj;

	UPROPERTY()
	UObject* AttackStrategyObj;

	IEnemyState* CurrentState;
	IAttackStrategy* AttackStrategy;

	UPROPERTY()
	AActor* PlayerTarget;
};