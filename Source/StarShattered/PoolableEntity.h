#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PoolableEntity.generated.h"

UINTERFACE(MinimalAPI)
class UPoolableEntity : public UInterface
{
    GENERATED_BODY()
};

class STARSHATTERED_API IPoolableEntity
{
    GENERATED_BODY()

public:
    // Se llama cuando el objeto sale del Pool (para reactivar colisiones, IA, mallas)
    virtual void OnDeactivatedFromPool() = 0;

    // Se llama cuando el objeto muere/explota y regresa al Pool (para apagar físicas y ocultarlo)
    virtual void OnReturnedToPool() = 0;
};