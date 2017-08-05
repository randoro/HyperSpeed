// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "HyperSpeedGameMode.h"
#include "LevelGenerator.generated.h"

UCLASS()
class HYPERSPEED_API ALevelGenerator : public AActor
{
	GENERATED_BODY()

	
	class AHyperSpeedGameMode* GameMode;
	
public:	
	// Sets default values for this actor's properties
	ALevelGenerator();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void GenerateSegment(FTransform LaneLocation);

	
	
};
