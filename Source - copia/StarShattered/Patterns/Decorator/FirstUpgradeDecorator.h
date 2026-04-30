#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FirstUpgradeDecorator.generated.h"

class AStarShatteredCharacter;

/**
 * UFirstUpgradeDecorator
 * Implements the Decorator Pattern (adapted to UE via Actor Component)
 * to dynamically add capabilities to the player (Rover).
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STARSHATTERED_API UFirstUpgradeDecorator : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFirstUpgradeDecorator();

	/** 
	 * Registers an enemy defeat and evaluates the condition.
	 */
	UFUNCTION(BlueprintCallable, Category = "Upgrades")
	void NotifyEnemyDefeated();

	/**
	 * Applies the decorator stats to the character.
	 */
	UFUNCTION(BlueprintCallable, Category = "Upgrades")
	void ApplyUpgrade(AStarShatteredCharacter* TargetCharacter);

protected:
	virtual void BeginPlay() override;

private:
	// Cantidad de enemigos derrotados actualmente
	int32 DefeatedEnemiesCount;

	// Condición para aplicar la mejora
	const int32 RequiredEnemiesForUpgrade = 15;

	// Evitar aplicar múltiples veces
	bool bUpgradeApplied;
};
