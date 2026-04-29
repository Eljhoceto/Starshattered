#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectPoolManager.generated.h"

// Envolvemos el TArray en un USTRUCT para que UPROPERTY lo proteja del Garbage Collector
USTRUCT()
struct FPoolContainer
{
    GENERATED_BODY()

    UPROPERTY()
    TArray<AActor*> InactiveActors;
};

UCLASS()
class STARSHATTERED_API AObjectPoolManager : public AActor
{
    GENERATED_BODY()

public:
    AObjectPoolManager();

    // Función para pre-cargar la memoria (Evita tirones al inicio del nivel)
    void InitializePoolForClass(TSubclassOf<AActor> ActorClass, int32 InitialSize);

    // Tu Fábrica llamará a esto en lugar de SpawnActor
    AActor* AcquireActor(TSubclassOf<AActor> ActorClass, const FTransform& SpawnTransform);

    // Los enemigos llamarán a esto cuando su salud llegue a 0
    void ReturnActor(AActor* ActorToReturn);

private:
    UPROPERTY()
    TMap<TSubclassOf<AActor>, FPoolContainer> PoolDictionary;
};