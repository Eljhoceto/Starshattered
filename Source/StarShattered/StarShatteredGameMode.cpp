// Copyright Epic Games, Inc. All Rights Reserved.

#include "StarShatteredGameMode.h"
#include "StarShatteredCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Patterns/Facade/DifficultyFacade.h"
#include "Patterns/Builder/EarthLevelBuilder.h"
#include "Patterns/Decorator/FirstUpgradeDecorator.h"
#include "Engine/Engine.h"

DEFINE_LOG_CATEGORY_STATIC(LogStarShatteredGameMode, Log, All);

AStarShatteredGameMode::AStarShatteredGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AStarShatteredGameMode::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogStarShatteredGameMode, Display, TEXT("StarShatteredGameMode: Initializando Sistemas del Nivel 1 (La Tierra)..."));

	// 1. Instanciar y configurar la fachada de dificultad
	DifficultySystem = NewObject<UDifficultyFacade>(this);
	if (DifficultySystem)
	{
		DifficultySystem->SetDifficultyLevel(EGameDifficulty::Medium);
		DifficultySystem->ApplyLevel1Settings();
		UE_LOG(LogStarShatteredGameMode, Log, TEXT("StarShatteredGameMode: DifficultyFacade instanciado y configurado con exito."));
	}

	// 2. Instanciar y ejecutar el constructor del nivel
	LevelBuilderSystem = NewObject<UEarthLevelBuilder>(this);
	if (LevelBuilderSystem)
	{
		LevelBuilderSystem->BuildLevel(GetWorld());
		UE_LOG(LogStarShatteredGameMode, Log, TEXT("StarShatteredGameMode: EarthLevelBuilder ha completado su secuencia de inicializacion."));
	}
}

void AStarShatteredGameMode::CheckVictoryCondition(int32 RemainingEnemies)
{
	if (RemainingEnemies > 0)
	{
		return; // Aun quedan enemigos, la oleada continua
	}

	UE_LOG(LogStarShatteredGameMode, Display, TEXT("StarShatteredGameMode: ¡Nivel 1 despejado! Todos los enemigos han sido derrotados."));

	// Instanciar el FirstUpgradeDecorator
	RewardDecorator = NewObject<UFirstUpgradeDecorator>(this);
	
	if (RewardDecorator)
	{
		// Validar que el mundo existan
		if (UWorld* World = GetWorld())
		{
			if (APlayerController* PC = World->GetFirstPlayerController())
			{
				// Asegurarnos de que el puntero sea un Rover valido antes de aplicar logica
				AStarShatteredCharacter* Rover = Cast<AStarShatteredCharacter>(PC->GetPawn());
				
				if (Rover)
				{
					// ¡Aplicar el patron Decorator al personaje!
					RewardDecorator->WrapCharacter(Rover);

					// Extraer los nuevos stats logicos resultantes
					float FinalShield = RewardDecorator->GetMaxShield();
					float FinalArmor = RewardDecorator->GetArmorResistance();

					// Notificacion visual en pantalla con color verde
					if (GEngine)
					{
						GEngine->AddOnScreenDebugMessage(-1, 8.0f, FColor::Green, TEXT("¡Nivel 1 Completado! Rover ha sido mejorado: +Escudo y +Armadura"));
					}

					// Reflejar contundentemente los nuevos valores actualizados en logs
					UE_LOG(LogStarShatteredGameMode, Log, TEXT("StarShatteredGameMode -> Decorator aplicado con exito. Nuevas Stats:"));
					UE_LOG(LogStarShatteredGameMode, Log, TEXT("  - Escudo Maximo: %.1f"), FinalShield);
					UE_LOG(LogStarShatteredGameMode, Log, TEXT("  - Resistencia de Armadura: %.1f"), FinalArmor);
				}
				else
				{
					UE_LOG(LogStarShatteredGameMode, Warning, TEXT("StarShatteredGameMode: Se alcanzo la victoria, pero Rover (AStarShatteredCharacter) no es valido o es nulo."));
				}
			}
		}
	}
}
