// Copyright Epic Games, Inc. All Rights Reserved.

#include "StarShatteredGameMode.h"
#include "StarShatteredCharacter.h"
#include "Patterns/Builder/EarthLevelBuilder.h"
#include "Patterns/Facade/DifficultyFacade.h"
#include "Patterns/Decorator/FirstUpgradeDecorator.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "CobrixBasic.h"

AStarShatteredGameMode::AStarShatteredGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	LevelBuilder = nullptr;
	DifficultyFacade = nullptr;
	FirstUpgradeDecorator = nullptr;
}

void AStarShatteredGameMode::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (World)
	{
		// Instanciar el Facade ANTES del Builder para que el Builder pueda usarlo
		DifficultyFacade = NewObject<UDifficultyFacade>(this, UDifficultyFacade::StaticClass());

		// Instanciar el Builder
		LevelBuilder = World->SpawnActor<AEarthLevelBuilder>(AEarthLevelBuilder::StaticClass());
		if (LevelBuilder)
		{
			LevelBuilder->BuildLevel();

			// Tarea 3: Conectar el Decorator a las muertes de los enemigos
			for (AActor* EnemyActor : LevelBuilder->GetSpawnedEnemies())
			{
				if (ACobrixBasic* Enemy = Cast<ACobrixBasic>(EnemyActor))
				{
					Enemy->OnEnemyDead.AddDynamic(this, &AStarShatteredGameMode::OnEnemyDefeated);
				}
			}
		}

		// Instanciar el Decorator
		// Casting Correcto: Usando AStarShatteredCharacter y asegurando el include correcto
		AStarShatteredCharacter* PlayerCharacter = Cast<AStarShatteredCharacter>(World->GetFirstPlayerController() ? World->GetFirstPlayerController()->GetPawn() : nullptr);
		
		if (PlayerCharacter)
		{
			FirstUpgradeDecorator = NewObject<UFirstUpgradeDecorator>(PlayerCharacter, UFirstUpgradeDecorator::StaticClass());
			if (FirstUpgradeDecorator)
			{
				FirstUpgradeDecorator->RegisterComponent();
				
				// La mejora se activará automáticamente a través del sistema de eventos cuando mueran 15 enemigos.
				// FirstUpgradeDecorator->ApplyUpgrade(PlayerCharacter);
			}
		}
	}
}

void AStarShatteredGameMode::OnEnemyDefeated()
{
	if (FirstUpgradeDecorator)
	{
		FirstUpgradeDecorator->NotifyEnemyDefeated();
	}
}

