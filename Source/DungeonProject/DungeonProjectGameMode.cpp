// Copyright Epic Games, Inc. All Rights Reserved.

#include "DungeonProjectGameMode.h"
#include "DungeonProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADungeonProjectGameMode::ADungeonProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
