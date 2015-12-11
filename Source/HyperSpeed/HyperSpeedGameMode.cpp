// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "HyperSpeed.h"
#include "HyperSpeedGameMode.h"
#include "HyperSpeedPawn.h"

AHyperSpeedGameMode::AHyperSpeedGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AHyperSpeedPawn::StaticClass();
}

