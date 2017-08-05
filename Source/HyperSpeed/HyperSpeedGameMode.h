// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "GameFramework/GameMode.h"
#include "LevelGenerator.h"
#include "HyperSpeedGameMode.generated.h"


UCLASS(minimalapi)
class AHyperSpeedGameMode : public AGameMode
{
	GENERATED_BODY()

	
	


public:
	AHyperSpeedGameMode();

	class ALevelGenerator* LevelGenerator;
};



