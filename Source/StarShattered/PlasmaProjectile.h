#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StarshatteredProduct.h" // Interfaz de Fábrica
#include "PoolableEntity.h"      // Interfaz de Pool
#include "PlasmaProjectile.generated.h"

// Declaraciones anticipadas para mejorar el tiempo de compilación
class USphereComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class STARSHATTERED_API APlasmaProjectile : public AActor, public IStarshatteredProduct, public IPoolableEntity
{
    GENERATED_BODY()

public:
    APlasmaProjectile();

    // --- Implementación de IStarshatteredProduct (Fábrica) ---
    virtual void InitializeProduct() override;

    // --- Implementación de IPoolableEntity (Object Pool) ---
    virtual void OnDeactivatedFromPool() override;
    virtual void OnReturnedToPool() override;

protected:
    // Componentes de alto rendimiento
    UPROPERTY(VisibleAnywhere, Category = "Components")
    USphereComponent* CollisionComponent;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* ProjectileMesh;

    UPROPERTY(VisibleAnywhere, Category = "Movement")
    UProjectileMovementComponent* ProjectileMovement;

    // Configuración del proyectil (GDD: Única arma que daña a los Cobrix [cite: 17])
    UPROPERTY(EditAnywhere, Category = "Combat")
    float DamageValue = 50.0f;
};