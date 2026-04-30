#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EarthLevelBuilder.generated.h"

class AStarShatteredCharacter;
class ACharacter;

/**
 * AEarthLevelBuilder
 * Implements the Builder Pattern to construct Level 1.
 */
UCLASS()
class STARSHATTERED_API AEarthLevelBuilder : public AActor
{
	GENERATED_BODY()
	
public:	
	AEarthLevelBuilder();

	const TArray<AActor*>& GetSpawnedEnemies() const { return SpawnedEnemies; }

	/**
	 * Construye el Nivel 1.
	 * Spawnea el jugador y 15 enemigos de la clase especificada en un radio de 2000 unidades.
	 */
	UFUNCTION(BlueprintCallable, Category = "Level Builder")
	void BuildLevel();

	/**
	 * Construye la nave de escape de Robert en la ubicación especificada.
	 */
	UFUNCTION(BlueprintCallable, Category = "Level Builder")
	void BuildEscapeShip(FVector Location);

	// Clase Blueprint del protagonista (Rover)
	UPROPERTY(EditAnywhere, Category = "Level Design")
	TSubclassOf<AStarShatteredCharacter> RoverBlueprintClass;

	// Clase genérica de enemigo a spawnear
	UPROPERTY(EditAnywhere, Category = "Level Design")
	TSubclassOf<ACharacter> EnemyClassToSpawn;

	// Clase de la Nave de Robert
	UPROPERTY(EditAnywhere, Category = "Level Design")
	TSubclassOf<class AActor> RobertShipClass;

protected:
	virtual void BeginPlay() override;

private:
	// Referencia al jugador instanciado
	UPROPERTY(VisibleAnywhere, Category = "Level Builder")
	AStarShatteredCharacter* SpawnedPlayer;

	// Referencias a los enemigos instanciados
	UPROPERTY(VisibleAnywhere, Category = "Level Builder")
	TArray<AActor*> SpawnedEnemies;
};
