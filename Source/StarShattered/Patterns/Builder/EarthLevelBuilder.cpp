#include "EarthLevelBuilder.h"
#include "../../StarShatteredCharacter.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "../../StarShatteredGameMode.h"
#include "../Facade/DifficultyFacade.h"
#include "../../CobrixBasic.h"

namespace
{
	// Enemy spawn safety constraints requested by architecture:
	// - X/Y must be within [-400, 400] (central floor; avoid walls)
	// - Z must be snapped to ground to avoid falling off-map
	constexpr float kEnemySpawnMinXY = -400.0f;
	constexpr float kEnemySpawnMaxXY = 400.0f;
	constexpr float kTraceStartZ = 2500.0f;
	constexpr float kTraceEndZ = -5000.0f;
	constexpr float kSpawnZOffset = 90.0f; // roughly capsule half-height for humanoids
	constexpr int32 kMaxSpawnAttemptsPerEnemy = 12;
	constexpr float kMaxGroundZAbovePlayer = 50.0f;

	static bool TryFindGroundZ(UWorld* World, const FVector2D& XY, float& OutGroundZ)
	{
		if (!World) return false;

		const FVector Start(XY.X, XY.Y, kTraceStartZ);
		const FVector End(XY.X, XY.Y, kTraceEndZ);

		FHitResult Hit;
		FCollisionQueryParams Params(SCENE_QUERY_STAT(EarthLevelBuilder_EnemySpawnTrace), /*bTraceComplex*/ false);
		Params.bReturnPhysicalMaterial = false;

		const bool bHit = World->LineTraceSingleByChannel(Hit, Start, End, ECC_WorldStatic, Params);
		if (!bHit) return false;

		OutGroundZ = Hit.Location.Z;
		return true;
	}
}

AEarthLevelBuilder::AEarthLevelBuilder()
{
	PrimaryActorTick.bCanEverTick = false;
	SpawnedPlayer = nullptr;

	RoverBlueprintClass = AStarShatteredCharacter::StaticClass();
	EnemyClassToSpawn = ACobrixBasic::StaticClass();
	RobertShipClass = AActor::StaticClass();
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
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

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
	constexpr int NumberOfEnemies = 15;

	// IMPORTANTE: Aquí deberías tener una variable (TSubclassOf<AActor>) 
	// que definiremos en el .h para que elijas al enemigo desde el editor.
	if (EnemyClassToSpawn)
	{
		SpawnedEnemies.Reset();

		int EnemiesSpawned = 0;
		const float MaxAllowedGroundZ = PlayerSpawnLocation.Z + kMaxGroundZAbovePlayer;

		// CRITICAL: only increment when we successfully spawned an enemy that passed validation.
		while (EnemiesSpawned < 15)
		{
			// No "give up" limit: keep trying until we get a valid ground and a successful spawn.
			while (true)
			{
				const float RandomX = FMath::RandRange(kEnemySpawnMinXY, kEnemySpawnMaxXY);
				const float RandomY = FMath::RandRange(kEnemySpawnMinXY, kEnemySpawnMaxXY);

				float GroundZ = 0.0f;
				if (TryFindGroundZ(World, FVector2D(RandomX, RandomY), GroundZ))
				{
					// Height validation: reject "ground" positions above the central floor (walls/ramps/etc.)
					if (GroundZ > MaxAllowedGroundZ)
					{
						continue;
					}

					const FVector EnemySpawnLocation(RandomX, RandomY, GroundZ + kSpawnZOffset);
					AActor* NewEnemy = World->SpawnActor<AActor>(EnemyClassToSpawn, EnemySpawnLocation, FRotator::ZeroRotator, SpawnParams);
					if (NewEnemy)
					{
						SpawnedEnemies.Add(NewEnemy);
						EnemiesSpawned++;
						break;
					}
				}
			}
		}
	}

	// Tarea 2: Obtener referencia al DifficultyFacade del GameMode y configurar enemigos
	if (AStarShatteredGameMode* GameMode = Cast<AStarShatteredGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		if (UDifficultyFacade* Facade = GameMode->GetDifficultyFacade())
		{
			Facade->ConfigureEnemiesForLevel(EDifficultyLevel::Medium, SpawnedEnemies);
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
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		World->SpawnActor<AActor>(RobertShipClass, Location, FRotator::ZeroRotator, SpawnParams);
	}
}