#include "EarthLevelBuilder.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "../../StarShatteredCharacter.h"

UEarthLevelBuilder::UEarthLevelBuilder()
{
	RoverCharacter = nullptr;
}

void UEarthLevelBuilder::BuildLevel(UWorld* WorldContext)
{
	if (!WorldContext) return;

	// El Builder define y encadena los pasos necesarios para inicializar el Nivel 1.
	BuildPlayerCharacter(WorldContext);
	BuildWaveManager(WorldContext);
	BuildPickUps(WorldContext);
}

void UEarthLevelBuilder::BuildPlayerCharacter(UWorld* WorldContext)
{
	// NOTA DE INTEGRACIÓN EN GAMEMODE:
	// Aquí encontramos a Rover para configurar el inicio del nivel a pie.
	APlayerController* PC = WorldContext->GetFirstPlayerController();
	if (PC)
	{
		RoverCharacter = Cast<AStarShatteredCharacter>(PC->GetPawn());
		if (RoverCharacter)
		{
			// Configurar estado de Rover para combate a pie
			// P.ej. fijar rotación de cámara, deshabilitar vuelo, etc.
		}
	}
}

void UEarthLevelBuilder::BuildWaveManager(UWorld* WorldContext)
{
	// NOTA DE INTEGRACIÓN EN GAMEMODE:
	// Prepara el gestor de la única oleada de 10 a 15 naves Cobrix.
	// Por ejemplo:
	// AWaveManager* WaveManager = WorldContext->SpawnActor<AWaveManager>(...);
	// WaveManager->PrepareWave("CobrixBasic", FMath::RandRange(10, 15));
}

void UEarthLevelBuilder::BuildPickUps(UWorld* WorldContext)
{
	// NOTA DE INTEGRACIÓN EN GAMEMODE:
	// Distribuir pick-ups. Depende de las clases C++ concretas que utilices.
	// Por ejemplo:
	// FVector HealthLoc(-500.f, 200.f, 50.f);
	// WorldContext->SpawnActor<APickUp>(RedHealthClass, HealthLoc, FRotator::ZeroRotator);
	
	// FVector ShieldLoc(500.f, -200.f, 50.f);
	// WorldContext->SpawnActor<APickUp>(BlueShieldClass, ShieldLoc, FRotator::ZeroRotator);
}
