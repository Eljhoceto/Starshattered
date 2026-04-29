#include "ObjectPoolManager.h"
#include "Engine/World.h"
#include "PoolableEntity.h" // Nuestra interfaz

AObjectPoolManager::AObjectPoolManager()
{
    PrimaryActorTick.bCanEverTick = false;
}

// 1. EL "WARM-UP" (Reserva de memoria al inicio del nivel)
void AObjectPoolManager::InitializePoolForClass(TSubclassOf<AActor> ActorClass, int32 InitialSize)
{
    if (!ActorClass || !GetWorld()) return;

    // Buscamos o creamos el contenedor para esta clase específica (ej. APlasmaProjectile)
    FPoolContainer& Container = PoolDictionary.FindOrAdd(ActorClass);
    Container.InactiveActors.Reserve(InitialSize);

    for (int32 i = 0; i < InitialSize; ++i)
    {
        // Instanciamos el proyectil oculto en el origen del mundo
        AActor* NewActor = GetWorld()->SpawnActor<AActor>(ActorClass, FVector::ZeroVector, FRotator::ZeroRotator);

        if (NewActor)
        {
            // Lo apagamos inmediatamente
            NewActor->SetActorHiddenInGame(true);
            NewActor->SetActorEnableCollision(false);
            NewActor->SetActorTickEnabled(false);

            if (IPoolableEntity* PoolableActor = Cast<IPoolableEntity>(NewActor))
            {
                PoolableActor->OnReturnedToPool();
            }

            Container.InactiveActors.Add(NewActor);
        }
    }

    UE_LOG(LogTemp, Display, TEXT("ObjectPool: Pre-cargados %d objetos de la clase %s"), InitialSize, *ActorClass->GetName());
}

// 2. LA EXTRACCIÓN (Cuando la Fábrica pide un proyectil para disparar)
AActor* AObjectPoolManager::AcquireActor(TSubclassOf<AActor> ActorClass, const FTransform& SpawnTransform)
{
    if (!ActorClass) return nullptr;

    FPoolContainer* Container = PoolDictionary.Find(ActorClass);

    // Si tenemos proyectiles inactivos disponibles, reciclamos el último
    if (Container && Container->InactiveActors.Num() > 0)
    {
        AActor* RecycledActor = Container->InactiveActors.Pop();

        RecycledActor->SetActorTransform(SpawnTransform);
        RecycledActor->SetActorHiddenInGame(false);
        RecycledActor->SetActorEnableCollision(true);
        RecycledActor->SetActorTickEnabled(true);

        if (IPoolableEntity* PoolableActor = Cast<IPoolableEntity>(RecycledActor))
        {
            PoolableActor->OnDeactivatedFromPool();
        }
        return RecycledActor;
    }

    // CONTINGENCIA: Si Rover dispara rapidísimo y agota el Pool, spawneamos uno nuevo de emergencia.
    // En un entorno ideal, el InitialSize debería ser lo suficientemente grande para no llegar nunca aquí.
    UE_LOG(LogTemp, Warning, TEXT("ObjectPool: Pool agotado para %s. Instanciando uno nuevo de emergencia."), *ActorClass->GetName());

    AActor* EmergencyActor = GetWorld()->SpawnActor<AActor>(ActorClass, SpawnTransform);
    if (IPoolableEntity* PoolableActor = Cast<IPoolableEntity>(EmergencyActor))
    {
        PoolableActor->OnDeactivatedFromPool();
    }
    return EmergencyActor;
}

// 3. EL RECICLAJE (Cuando el proyectil impacta o sale del mapa)
void AObjectPoolManager::ReturnActor(AActor* ActorToReturn)
{
    if (!ActorToReturn) return;

    UClass* ActorClass = ActorToReturn->GetClass();

    // Detenemos el proyectil

    if (IPoolableEntity* PoolableActor = Cast<IPoolableEntity>(ActorToReturn))
    {
        PoolableActor->OnReturnedToPool();
    }

    // Lo volvemos "fantasma"
    ActorToReturn->SetActorHiddenInGame(true);
    ActorToReturn->SetActorEnableCollision(false);
    ActorToReturn->SetActorTickEnabled(false);
    ActorToReturn->SetActorLocation(FVector::ZeroVector);

    // Lo guardamos en el diccionario
    PoolDictionary.FindOrAdd(ActorClass).InactiveActors.Add(ActorToReturn);
}