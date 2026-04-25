#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FirstUpgradeDecorator.generated.h"

class AStarShatteredCharacter;

/**
 * UFirstUpgradeDecorator
 * Patrón Decorator diseñado para "envolver" a AStarShatteredCharacter (Rover)
 * y añadir funcionalidad para incrementar capacidad de escudo y armadura.
 */
UCLASS()
class STARSHATTERED_API UFirstUpgradeDecorator : public UObject
{
	GENERATED_BODY()

public:
	UFirstUpgradeDecorator();

	// Inicializa el decorador apuntando a nuestra instancia de Rover
	UFUNCTION()
	void WrapCharacter(AStarShatteredCharacter* InCharacter);

	// Implementamos los métodos con la lógica extendida.
	// NOTA: Para un Decorator puro, la clase base (AStarShatteredCharacter) debería 
	// declarar estos métodos como virtual, y este llamaría al "WrappedRover->GetMaxShield()".
	virtual float GetMaxShield() const;
	virtual float GetArmorResistance() const;

protected:
	// Referencia a nuestro personaje encapsulado
	UPROPERTY(VisibleAnywhere, Category = "Decorator")
	AStarShatteredCharacter* WrappedRover;

	// Mejoras otorgadas por finalizar el Nivel 1
	float AddedMaxShield;
	float AddedArmorResistance;
};
