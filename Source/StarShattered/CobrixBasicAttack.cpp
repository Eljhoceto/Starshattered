// Fill out your copyright notice in the Description page of Project Settings.

#include "CobrixBasicAttack.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "ObjectPoolManager.h"
#include "Kismet/GameplayStatics.h"
#include "PlasmaProjectile.h"

void UCobrixBasicAttack::ExecuteAttack(AActor* Target)
{
	if (!Target)
	{
		return;
	}

	AAIController* AICon = Cast<AAIController>(GetOuter());
	if (!AICon)
	{
		return;
	}

	APawn* EnemyPawn = AICon->GetPawn();
	if (!EnemyPawn)
	{
		return;
	}

	// --- 1. APLICAR DAÑO DIRECTO ---
	UGameplayStatics::ApplyDamage(Target, 15.0f, AICon, EnemyPawn, nullptr);

	UE_LOG(LogTemp, Warning, TEXT("Disparando plasma lineal hacia el jugador."));

	// --- 2. LÓGICA VISUAL DEL PROYECTIL ---
	FVector SpawnLocation = EnemyPawn->GetActorLocation() + (EnemyPawn->GetActorForwardVector() * 150.0f);
	FRotator SpawnRotation = EnemyPawn->GetActorRotation();
	FTransform SpawnTransform(SpawnRotation, SpawnLocation);

	UWorld* World = EnemyPawn->GetWorld();
	if (World)
	{
		AObjectPoolManager* PoolManager = Cast<AObjectPoolManager>(UGameplayStatics::GetActorOfClass(World, AObjectPoolManager::StaticClass()));

		if (PoolManager)
		{
			AActor* Projectile = PoolManager->AcquireActor(APlasmaProjectile::StaticClass(), SpawnTransform);
			if (Projectile)
			{
				Projectile->SetInstigator(EnemyPawn);
				Projectile->SetOwner(EnemyPawn);
			}
		}
	}
}