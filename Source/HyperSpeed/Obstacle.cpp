// Fill out your copyright notice in the Description page of Project Settings.

#include "HyperSpeed.h"
#include "Obstacle.h"


// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaneMesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ObstacleMesh(TEXT("/Game/Geometry/Meshes/1M_Cube.1M_Cube"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> ObstacleCheckerMat(TEXT("/Game/StarterContent/Materials/M_Metal_Burnished_Steel.M_Metal_Burnished_Steel"));

	//SceneComponent
	RootComponent = SceneComponent;

	//Middle
	MeshComponent->AttachTo(RootComponent);
	//MeshComponent->SetCollisionProfileName(UCollisionProfile::);
	MeshComponent->SetStaticMesh(ObstacleMesh.Object);
	MeshComponent->SetMaterial(0, ObstacleCheckerMat.Object);

}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObstacle::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

