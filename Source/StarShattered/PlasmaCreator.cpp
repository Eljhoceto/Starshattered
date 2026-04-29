#include "PlasmaCreator.h"

AActor* APlasmaCreator::FactoryMethod(const FTransform& SpawnTransform)
{
    // 1. Verificaciones de seguridad críticas en C++
    if (!PoolManager)
    {
        UE_LOG(LogTemp, Error, TEXT("PlasmaCreator: ¡Falta asignar el PoolManager!"));
        return nullptr;
    }

    if (!PlasmaClass)
    {
        UE_LOG(LogTemp, Error, TEXT("PlasmaCreator: ¡Falta asignar la PlasmaClass (APlasmaProjectile)!"));
        return nullptr;
    }

    // 2. Extracción optimizada de memoria
    // En lugar de instanciar un nuevo proyectil, el creador le exige uno al Pool.
    AActor* PooledProjectile = PoolManager->AcquireActor(PlasmaClass, SpawnTransform);

    return PooledProjectile;
}