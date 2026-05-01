// Fill out your copyright notice in the Description page of Project Settings.

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CobrixBasic.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnemyDead);

UCLASS()
class STARSHATTERED_API ACobrixBasic : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACobrixBasic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnEnemyDead OnEnemyDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float BaseDamage;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void TakeEnemyDamage(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetHealth(float NewHealth) { Health = NewHealth; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetDamage(float NewDamage) { BaseDamage = NewDamage; }

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:
	UPROPERTY(EditAnywhere, Category = "AI|Combat")
	float AttackRange = 150.0f;

	UPROPERTY(EditAnywhere, Category = "AI|Combat")
	float AttackCooldownSeconds = 2.0f;

	UPROPERTY(EditAnywhere, Category = "AI|Combat")
	float ShootRange = 3000.0f;

	UPROPERTY(EditAnywhere, Category = "AI|Combat")
	float ShootCooldownSeconds = 3.0f;

	UPROPERTY(EditAnywhere, Category = "AI|Movement")
	float ChaseAcceptanceRadius = 60.0f;

	UPROPERTY(EditAnywhere, Category = "AI|Combat")
	TObjectPtr<class UAnimMontage> AttackMontage = nullptr;

	float LastAttackTimeSeconds = -10000.0f;
	float LastShootTimeSeconds = -10000.0f;
	bool bWarnedNavMesh = false;
};





