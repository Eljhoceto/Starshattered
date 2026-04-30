#include "FirstUpgradeDecorator.h"
#include "StarShattered/StarShatteredCharacter.h"

UFirstUpgradeDecorator::UFirstUpgradeDecorator()
{
	PrimaryComponentTick.bCanEverTick = false;
	DefeatedEnemiesCount = 0;
	bUpgradeApplied = false;
}

void UFirstUpgradeDecorator::BeginPlay()
{
	Super::BeginPlay();
}

void UFirstUpgradeDecorator::NotifyEnemyDefeated()
{
	if (bUpgradeApplied) return;

	DefeatedEnemiesCount++;

	if (DefeatedEnemiesCount >= RequiredEnemiesForUpgrade)
	{
		AStarShatteredCharacter* PlayerCharacter = Cast<AStarShatteredCharacter>(GetOwner());
		if (PlayerCharacter)
		{
			ApplyUpgrade(PlayerCharacter);
		}
	}
}

void UFirstUpgradeDecorator::ApplyUpgrade(AStarShatteredCharacter* TargetCharacter)
{
	if (!TargetCharacter || bUpgradeApplied) return;

	// Añade: +50 escudo máximo, +15 resistencia
	TargetCharacter->MaxShield += 50.0f;
	TargetCharacter->Resistance += 15.0f;

	bUpgradeApplied = true;

	// TODO: CONEXIÓN EQUIPO (Desarrollador A)
	// Emitir evento visual/sonoro de 'Level Up' aquí.
}
