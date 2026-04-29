#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "StarshatteredProduct.generated.h"

UINTERFACE(MinimalAPI)
class UStarshatteredProduct : public UInterface
{
    GENERATED_BODY()
};

class STARSHATTERED_API IStarshatteredProduct
{
    GENERATED_BODY()

public:
    // Método que todo producto debe implementar
    virtual void InitializeProduct() = 0;
};