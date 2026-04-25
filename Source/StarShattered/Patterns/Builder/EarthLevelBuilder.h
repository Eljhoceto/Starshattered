#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EarthLevelBuilder.generated.h"

class AStarShatteredCharacter;

/**
 * UEarthLevelBuilder
 * Patrón Builder para construir y configurar la arquitectura inicial del Nivel 1 (La Tierra).
 */
UCLASS()
class STARSHATTERED_API UEarthLevelBuilder : public UObject
{
	GENERATED_BODY()

public:
	UEarthLevelBuilder();

	// Inicia el proceso de construcción secuencial del nivel
	virtual void BuildLevel(UWorld* WorldContext);

	// Posiciona a Rover para combate a pie (tercera persona)
	virtual void BuildPlayerCharacter(UWorld* WorldContext);

	// Prepara el gestor de la oleada enemiga
	virtual void BuildWaveManager(UWorld* WorldContext);

	// Distribuye los primeros pick-ups (Rojo para salud y Azul para escudo)
	virtual void BuildPickUps(UWorld* WorldContext);

protected:
	UPROPERTY()
	AStarShatteredCharacter* RoverCharacter;
};
