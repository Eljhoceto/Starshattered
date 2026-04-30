#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DifficultyFacade.generated.h"

UENUM(BlueprintType)
enum class EDifficultyLevel : uint8
{
	Easy   UMETA(DisplayName = "Easy"),
	Medium UMETA(DisplayName = "Medium"),
	Hard   UMETA(DisplayName = "Hard")
};

/**
 * UDifficultyFacade
 * Implements the Facade Pattern to centralize level difficulty settings.
 */
UCLASS(Blueprintable, BlueprintType)
class STARSHATTERED_API UDifficultyFacade : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * Configures an array of spawned enemies based on the current level.
	 */
	UFUNCTION(BlueprintCallable, Category = "Difficulty")
	void ConfigureEnemiesForLevel(EDifficultyLevel Difficulty, const TArray<AActor*>& Enemies);
};
