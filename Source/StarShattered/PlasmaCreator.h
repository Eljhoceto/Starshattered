#pragma once

#include "CoreMinimal.h"
#include "EntityCreator.h" // Nuestra clase base abstracta
#include "PlasmaCreator.generated.h"

UCLASS()
class STARSHATTERED_API APlasmaCreator : public AEntityCreator
{
    GENERATED_BODY()

protected:
    // Referencia a la clase del proyectil que vamos a reciclar
    UPROPERTY(EditDefaultsOnly, Category = "Factory Configuration")
    TSubclassOf<AActor> PlasmaClass;

    // Sobrescribimos el Factory Method
    virtual AActor* FactoryMethod(const FTransform& SpawnTransform) override;
};