#include "FirstUpgradeDecorator.h"
#include "../../StarShatteredCharacter.h"

UFirstUpgradeDecorator::UFirstUpgradeDecorator()
{
	WrappedRover = nullptr;
	AddedMaxShield = 50.0f;       // Incremento de capacidad máxima de escudo
	AddedArmorResistance = 15.0f; // Incremento de la resistencia de armadura
}

void UFirstUpgradeDecorator::WrapCharacter(AStarShatteredCharacter* InCharacter)
{
	WrappedRover = InCharacter;
}

float UFirstUpgradeDecorator::GetMaxShield() const
{
	// Si WrappedRover es válido, aumentamos su escudo base.
	if (WrappedRover)
	{
		// Ahora que existe el metodo virtual, extraemos el valor real base del Rover:
		return WrappedRover->GetBaseMaxShield() + AddedMaxShield;
	}
	
	return AddedMaxShield;
}

float UFirstUpgradeDecorator::GetArmorResistance() const
{
	if (WrappedRover)
	{
		// Ahora que existe el metodo virtual, extraemos el valor real de armadura del Rover:
		return WrappedRover->GetBaseArmorResistance() + AddedArmorResistance;
	}

	return AddedArmorResistance;
}
