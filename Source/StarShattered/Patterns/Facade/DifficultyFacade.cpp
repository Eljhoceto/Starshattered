#include "DifficultyFacade.h"
#include "GameFramework/Actor.h"

void UDifficultyFacade::ConfigureEnemiesForLevel(EDifficultyLevel Difficulty, const TArray<AActor*>& Enemies)
{
	float TargetHealth = 100.0f;
	float TargetDamage = 10.0f;

	switch (Difficulty)
	{
		case EDifficultyLevel::Easy:
			TargetHealth = 50.0f;
			TargetDamage = 5.0f;
			break;
		case EDifficultyLevel::Medium:
			TargetHealth = 100.0f;
			TargetDamage = 10.0f;
			break;
		case EDifficultyLevel::Hard:
			TargetHealth = 200.0f;
			TargetDamage = 20.0f;
			break;
	}

	for (AActor* Enemy : Enemies)
	{
		if (Enemy)
		{
			// TODO: CONEXIÓN EQUIPO (Desarrollador B)
			// Llama a las funciones de salud y daño de la clase de enemigo aquí.
			// Ejemplo:
			// if (IMyEnemyInterface* EnemyRef = Cast<IMyEnemyInterface>(Enemy))
			// {
			//     EnemyRef->SetHealth(TargetHealth);
			//     EnemyRef->SetDamage(TargetDamage);
			// }
		}
	}
}

