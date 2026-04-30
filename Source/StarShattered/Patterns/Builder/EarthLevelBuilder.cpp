#include "EarthLevelBuilder.h"
#include "../../StarShatteredCharacter.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"

AEarthLevelBuilder::AEarthLevelBuilder()
{
	PrimaryActorTick.bCanEverTick = false;
	SpawnedPlayer = nullptr;
}

void AEarthLevelBuilder::BeginPlay()
{
	Super::BeginPlay();
}

void AEarthLevelBuilder::BuildLevel()
{
	UWorld* World = GetWorld();
	if (!World) return;

	// 1. Spawn Player (Rover)
	FVector PlayerSpawnLocation = GetActorLocation();
	FRotator PlayerSpawnRotation = FRotator::ZeroRotator;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// Aquí spawneamos al protagonista usando la clase Blueprint
	if (RoverBlueprintClass)
	{
		SpawnedPlayer = World->SpawnActor<AStarShatteredCharacter>(RoverBlueprintClass, PlayerSpawnLocation, PlayerSpawnRotation, SpawnParams);
	}
	else
	{
		// Fallback
		SpawnedPlayer = World->SpawnActor<AStarShatteredCharacter>(AStarShatteredCharacter::StaticClass(), PlayerSpawnLocation, PlayerSpawnRotation, SpawnParams);
	}

	// 2. Spawn de Enemigos usando una clase genérica
	// Esto permite que el Builder funcione sin importar qué nave cree el Dev B
	int32 NumberOfEnemies = 15;
	float SpawnRadius = 2000.0f;

	// IMPORTANTE: Aquí deberías tener una variable (TSubclassOf<AActor>) 
	// que definiremos en el .h para que elijas al enemigo desde el editor.
	if (EnemyClassToSpawn)
	{
		for (int32 i = 0; i < NumberOfEnemies; ++i)
		{
			FVector RandomOffset = FMath::VRand() * FMath::FRandRange(0.0f, SpawnRadius);
			RandomOffset.Z = 0.0f;
			FVector EnemySpawnLocation = PlayerSpawnLocation + RandomOffset;

			AActor* NewEnemy = World->SpawnActor<AActor>(EnemyClassToSpawn, EnemySpawnLocation, FRotator::ZeroRotator, SpawnParams);
			if (NewEnemy)
			{
				SpawnedEnemies.Add(NewEnemy);
			}
		}
	}
}

void AEarthLevelBuilder::BuildEscapeShip(FVector Location)
{
	UWorld* World = GetWorld();
	if (!World) return;

	if (RobertShipClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		World->SpawnActor<AActor>(RobertShipClass, Location, FRotator::ZeroRotator, SpawnParams);
	}
}