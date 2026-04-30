// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StarShatteredGameMode.generated.h"

// Forward Declarations
class AStarShatteredCharacter;
class AEarthLevelBuilder;
class UDifficultyFacade;
class UFirstUpgradeDecorator;

UCLASS(minimalapi)
class AStarShatteredGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AStarShatteredGameMode();

	UFUNCTION(BlueprintCallable, Category = "Patterns")
	UDifficultyFacade* GetDifficultyFacade() const { return DifficultyFacade; }

	UFUNCTION()
	void OnEnemyDefeated();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Patterns")
	AEarthLevelBuilder* LevelBuilder;

	UPROPERTY(VisibleAnywhere, Category = "Patterns")
	UDifficultyFacade* DifficultyFacade;

	UPROPERTY(VisibleAnywhere, Category = "Patterns")
	UFirstUpgradeDecorator* FirstUpgradeDecorator;
};
