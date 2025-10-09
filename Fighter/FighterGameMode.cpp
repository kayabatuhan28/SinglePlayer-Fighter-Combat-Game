// Copyright Epic Games, Inc. All Rights Reserved.

#include "FighterGameMode.h"
#include "FighterCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFighterGameMode::AFighterGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
