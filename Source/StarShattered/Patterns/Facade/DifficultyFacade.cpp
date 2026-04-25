#include "DifficultyFacade.h"
#include "Engine/Engine.h"

UDifficultyFacade::UDifficultyFacade()
{
	CurrentDifficulty = EGameDifficulty::Medium;
	BaseCobrixHealth = 100.0f;
	BaseCobrixDamage = 10.0f;
	LevelTimeLimit = 300.0f; // 5 minutos por defecto
}

void UDifficultyFacade::SetDifficultyLevel(EGameDifficulty NewDifficulty)
{
	CurrentDifficulty = NewDifficulty;
}

void UDifficultyFacade::ApplyLevel1Settings()
{
	// Lógica del Nivel 1: Ajustar vida y daño para la única oleada
	// (10 a 15 "Naves Cobrix básicas"), y modificar el tiempo límite del nivel tutorial.
	
	switch (CurrentDifficulty)
	{
		case EGameDifficulty::Easy:
			BaseCobrixHealth = 50.0f;
			BaseCobrixDamage = 5.0f;
			LevelTimeLimit = 600.0f; // Más tiempo en modo fácil
			break;
		case EGameDifficulty::Medium:
			BaseCobrixHealth = 100.0f;
			BaseCobrixDamage = 10.0f;
			LevelTimeLimit = 300.0f;
			break;
		case EGameDifficulty::Hard:
			BaseCobrixHealth = 200.0f;
			BaseCobrixDamage = 25.0f;
			LevelTimeLimit = 150.0f; // Menos tiempo en modo difícil
			break;
	}

	// NOTA DE INTEGRACIÓN EN GAMEMODE:
	// Esta fachada se inicializa desde AStarShatteredGameMode.
	// AWaveManager* WaveManager = GetWorld()->GetAuthGameMode()->GetWaveManager();
	// Si existe gestor, se aplican los parámetros de las 10~15 naves Cobrix.
	// WaveManager->SetWaveParams(10, 15, BaseCobrixHealth, BaseCobrixDamage);
	// GetWorld()->GetAuthGameMode()->SetLevelTimeLimit(LevelTimeLimit);
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Dificultad Aplicada -> Salud: %.1f, Danio: %.1f, Tiempo: %.1f"), BaseCobrixHealth, BaseCobrixDamage, LevelTimeLimit));
	}
}
