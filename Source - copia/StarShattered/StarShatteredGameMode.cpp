// Copyright Epic Games, Inc. All Rights Reserved.

#include "StarShatteredGameMode.h"
#include "StarShatteredCharacter.h"
#include "UObject/ConstructorHelpers.h"

AStarShatteredGameMode::AStarShatteredGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
