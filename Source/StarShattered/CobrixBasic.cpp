




#include "CobrixBasic.h"
#include "ObjectPoolManager.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "AIController.h"
#include "StarShatteredCharacter.h"
#include "Navigation/PathFollowingComponent.h"
#include "Engine/Engine.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlasmaProjectile.h"

// Sets default values
ACobrixBasic::ACobrixBasic()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = 100.0f;
	BaseDamage = 0.03f;

	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
	{
		MoveComp->MaxWalkSpeed = 350.0f;
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny"));
	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
		GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	}

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AAIController::StaticClass();
}

float ACobrixBasic::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (ActualDamage > 0.0f)
	{
		TakeEnemyDamage(ActualDamage);
	}
	return ActualDamage;
}

// Called when the game starts or when spawned
void ACobrixBasic::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACobrixBasic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GetWorld())
	{
		return;
	}

	AStarShatteredCharacter* Player = Cast<AStarShatteredCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (!Player)
	{
		return;
	}

	AAIController* AICon = Cast<AAIController>(GetController());
	if (!AICon)
	{
		return;
	}

	const FVector PlayerLocation = Player->GetActorLocation();
	const float DistToPlayer = FVector::Dist(GetActorLocation(), PlayerLocation);

	// Attack check (critical: distance-based in Tick for tight sync)
	if (DistToPlayer < 150.0f)
	{
		const float Now = GetWorld()->GetTimeSeconds();
		if ((Now - LastAttackTimeSeconds) >= AttackCooldownSeconds)
		{
			LastAttackTimeSeconds = Now;

			if (AttackMontage)
			{
				PlayAnimMontage(AttackMontage);
			}

			UGameplayStatics::ApplyDamage(Player, BaseDamage, AICon, this, nullptr);
		}
	}
	else if (DistToPlayer <= ShootRange)
	{
		if (AICon->LineOfSightTo(Player))
		{
			const float Now = GetWorld()->GetTimeSeconds();
			if ((Now - LastShootTimeSeconds) >= ShootCooldownSeconds)
			{
				LastShootTimeSeconds = Now;

				// Lógica visual del proyectil (similar a CobrixBasicAttack)
				FVector SpawnLocation = GetActorLocation() + (GetActorForwardVector() * 150.0f);
				FVector DirectionToPlayer = (PlayerLocation - SpawnLocation).GetSafeNormal();
				FRotator SpawnRotation = DirectionToPlayer.Rotation();
				FTransform SpawnTransform(SpawnRotation, SpawnLocation);

				AObjectPoolManager* PoolManager = Cast<AObjectPoolManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AObjectPoolManager::StaticClass()));
				if (PoolManager)
				{
					AActor* Projectile = PoolManager->AcquireActor(APlasmaProjectile::StaticClass(), SpawnTransform);
					if (Projectile)
					{
						Projectile->SetInstigator(this);
						Projectile->SetOwner(this);
					}
				}

				// Aplicar daño directo simulando el impacto del disparo (hitscan)
				UGameplayStatics::ApplyDamage(Player, 15.0f, AICon, this, nullptr);
			}
		}
	}

	// Chase when not in attack range
	const EPathFollowingRequestResult::Type MoveResult = AICon->MoveToActor(Player, ChaseAcceptanceRadius, /*bStopOnOverlap*/ true);
	if (MoveResult == EPathFollowingRequestResult::Failed)
	{
		if (!bWarnedNavMesh && GEngine)
		{
			bWarnedNavMesh = true;
			GEngine->AddOnScreenDebugMessage(
				-1,
				5.0f,
				FColor::Yellow,
				TEXT("CobrixBasic: MoveToActor FAILED. Possible missing/disabled NavMesh (RecastNavMesh) in the level.")
			);
		}
	}
}

// Called to bind functionality to input
void ACobrixBasic::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACobrixBasic::TakeEnemyDamage(float Amount)
{
	Health -= Amount;
	if (Health <= 0.0f)
	{
		OnEnemyDead.Broadcast();

		AObjectPoolManager* PoolManager = Cast<AObjectPoolManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AObjectPoolManager::StaticClass()));
		if (PoolManager)
		{
			PoolManager->ReturnActor(this);
		}
		else
		{
			Destroy();
		}
	}
}