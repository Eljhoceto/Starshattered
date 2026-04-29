// CobrixCreator.cpp
#include "CobrixCreator.h"

AActor* ACobrixCreator::FactoryMethod(const FTransform& SpawnTransform)
{
    // Verificamos que tengamos acceso al Pool y que la clase esté configurada
    if (!PoolManager || !CobrixClass)
    {
        UE_LOG(LogTemp, Error, TEXT("CobrixCreator: Falta PoolManager o CobrixClass!"));
        return nullptr;
    }

    // ¡CONEXIÓN REALIZADA! 
    // En lugar de crear memoria nueva, reciclamos una existente
    return PoolManager->AcquireActor(CobrixClass, SpawnTransform);
}