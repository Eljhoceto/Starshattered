#include "PlasmaProjectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

APlasmaProjectile::APlasmaProjectile()
{
    // Rendimiento: Desactivamos el Tick por completo
    PrimaryActorTick.bCanEverTick = false;

    // 1. Colisión simple (Esfera es lo más barato para la CPU)
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    CollisionComponent->InitSphereRadius(5.0f);
    CollisionComponent->SetCollisionProfileName(TEXT("Projectile"));
    RootComponent = CollisionComponent;

    // 2. Malla Visual
    ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    ProjectileMesh->SetupAttachment(RootComponent);
    ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // La malla no colisiona, solo la esfera

    // 3. Movimiento Optimizado
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMoveComp"));
    ProjectileMovement->UpdatedComponent = CollisionComponent;
    ProjectileMovement->InitialSpeed = 3000.0f;
    ProjectileMovement->MaxSpeed = 3000.0f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->ProjectileGravityScale = 0.0f; // Sin gravedad para disparos de plasma precisos
}

// Se llama cuando la Fábrica lo "crea" (lo saca del pool)
void APlasmaProjectile::InitializeProduct()
{
    UE_LOG(LogTemp, Display, TEXT("Plasma: Configurando daño para impactar Cobrix."));
}

// Se llama cuando el Pool lo ACTIVA para ser disparado
void APlasmaProjectile::OnDeactivatedFromPool()
{
    // Reactivamos el movimiento y las físicas
    ProjectileMovement->Velocity = GetActorForwardVector() * ProjectileMovement->InitialSpeed;
    ProjectileMovement->Activate();

    SetActorTickEnabled(true); // Solo si necesitas lógica específica, si no, déjalo en false
}

// Se llama cuando el proyectil impacta o muere (Regresa al pool)
void APlasmaProjectile::OnReturnedToPool()
{
    // LIMPIEZA CRÍTICA: Frenamos el proyectil para que no siga moviéndose en el "limbo"
    ProjectileMovement->StopMovementImmediately();
    ProjectileMovement->Deactivate();

    SetActorTickEnabled(false);
}