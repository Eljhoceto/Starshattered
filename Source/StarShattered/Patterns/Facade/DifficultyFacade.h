#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DifficultyFacade.generated.h"

UENUM()
enum class EGameDifficulty : uint8
{
	Easy,
	Medium,
	Hard
};

/**
 * UDifficultyFacade
 * Patrón Facade para gestionar la dificultad general del juego.
 * Interactúa con gestores de oleadas, enemigos y estado del juego de forma unificada.
 */
UCLASS()
class STARSHATTERED_API UDifficultyFacade : public UObject
{
	GENERATED_BODY()

public:
	UDifficultyFacade();

	// Establece la dificultad actual
	UFUNCTION()
	void SetDifficultyLevel(EGameDifficulty NewDifficulty);

	// Aplica las configuraciones de dificultad específicamente para el Nivel 1
	UFUNCTION()
	void ApplyLevel1Settings();

protected:
	EGameDifficulty CurrentDifficulty;

	// Valores base que serán modificados según la dificultad
	UPROPERTY(VisibleAnywhere, Category = "Difficulty")
	float BaseCobrixHealth;

	UPROPERTY(VisibleAnywhere, Category = "Difficulty")
	float BaseCobrixDamage;

	UPROPERTY(VisibleAnywhere, Category = "Difficulty")
	float LevelTimeLimit;
};
