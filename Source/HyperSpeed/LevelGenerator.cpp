// Fill out your copyright notice in the Description page of Project Settings.

#include "HyperSpeed.h"
#include "LevelGenerator.h"
#include "Obstacle.h"


// Sets default values
ALevelGenerator::ALevelGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelGenerator::BeginPlay()
{
	Super::BeginPlay();

	//Reference Gamemode
	GameMode = (AHyperSpeedGameMode*)GetWorld()->GetAuthGameMode();

	GameMode->LevelGenerator = this;
}

// Called every frame
void ALevelGenerator::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

//Called to create obstacles in a lane segment.
void ALevelGenerator::GenerateSegment(FTransform LaneLocation) 
{

	FVector newLocation = LaneLocation.GetLocation();
	newLocation.X += 10.0f;
	newLocation.Z += 100.0f;

	FTransform NewTransform = FTransform(LaneLocation.GetRotation(), newLocation, this->GetActorScale3D());
	
	AObstacle* NextLaneClass = GetWorld()->SpawnActor<AObstacle>(AObstacle::StaticClass(), newLocation, FRotator::ZeroRotator);

}

