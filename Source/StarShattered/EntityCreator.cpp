// EntityCreator.cpp (Código corregido)
#include "EntityCreator.h"
#include "StarshatteredProduct.h"

AEntityCreator::AEntityCreator()
{
    PrimaryActorTick.bCanEverTick = false;
}

AActor* AEntityCreator::SpawnEntity(const FTransform& SpawnTransform)
{
    AActor* NewEntity = FactoryMethod(SpawnTransform);

    if (NewEntity)
    {
        if (IStarshatteredProduct* ProductInterface = Cast<IStarshatteredProduct>(NewEntity))
        {
            ProductInterface->InitializeProduct();
        }
    }
    return NewEntity;
}