// CobrixCreator.h
#pragma once

#include "CoreMinimal.h"
#include "EntityCreator.h" // Vital: Heredamos de tu clase base Creadora
#include "CobrixCreator.generated.h"

UCLASS()
class STARSHATTERED_API ACobrixCreator : public AEntityCreator
{
    GENERATED_BODY()

protected:
    // 1. SOLUCIÓN AL ERROR DE 'CobrixClass':
    // Declaramos la variable para que el Creador sepa qué clase de enemigo va a reciclar.
    UPROPERTY(EditDefaultsOnly, Category = "Factory Configuration")
    TSubclassOf<AActor> CobrixClass;

    // 2. SOLUCIÓN AL ERROR DE 'FactoryMethod':
    // Declaramos explícitamente que estamos sobrescribiendo el método virtual puro de la clase padre.
    virtual AActor* FactoryMethod(const FTransform& SpawnTransform) override;
};