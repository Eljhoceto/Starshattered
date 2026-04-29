// EntityCreator.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectPoolManager.h" // Importante: ahora la fábrica conoce al Pool
#include "EntityCreator.generated.h"

UCLASS(Abstract)
class STARSHATTERED_API AEntityCreator : public AActor
{
    GENERATED_BODY()

public:
    AEntityCreator();

    // El Gestor de Memoria que inyectaremos en la fábrica
    UPROPERTY(EditAnywhere, Category = "Factory | Performance")
    AObjectPoolManager* PoolManager;

    // La operación principal sigue siendo la misma para el cliente
    AActor* SpawnEntity(const FTransform& SpawnTransform);

protected:
    // El Factory Method ahora tiene la responsabilidad de pedir al Pool
    virtual AActor* FactoryMethod(const FTransform& SpawnTransform) PURE_VIRTUAL(AEntityCreator::FactoryMethod, return nullptr;);
};