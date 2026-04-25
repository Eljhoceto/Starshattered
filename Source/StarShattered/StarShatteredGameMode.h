// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StarShatteredGameMode.generated.h"

UCLASS(minimalapi)
class AStarShatteredGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AStarShatteredGameMode();

	// Comprueba si se ha alcanzado la condicion de victoria de la oleada
	UFUNCTION(BlueprintCallable, Category = "Level Systems")
	void CheckVictoryCondition(int32 RemainingEnemies);

protected:
	virtual void BeginPlay() override;

private:
	// Instancia del sistema Facade para la dificultad
	UPROPERTY(VisibleAnywhere, Category = "Level Systems")
	class UDifficultyFacade* DifficultySystem;

	// Instancia del Builder para construir el entorno inicial del nivel
	UPROPERTY(VisibleAnywhere, Category = "Level Systems")
	class UEarthLevelBuilder* LevelBuilderSystem;

	// Instancia del Decorator que recompensa a Rover tras la victoria
	UPROPERTY(VisibleAnywhere, Category = "Level Systems")
	class UFirstUpgradeDecorator* RewardDecorator;
};



