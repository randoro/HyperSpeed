// Fill out your copyright notice in the Description page of Project Settings.

#include "HyperSpeed.h"
#include "Lane.h"


// Sets default values
ALane::ALane()
{

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/Geometry/Meshes/1M_Cube.1M_Cube"));
	// Create the mesh component
	LaneMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaneMesh"));
	RootComponent = LaneMeshComponent;
	LaneMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	LaneMeshComponent->SetStaticMesh(ShipMesh.Object);

	// Create the left mesh component
	LaneMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftLaneMesh"));
	LaneMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	LaneMeshComponent->SetStaticMesh(ShipMesh.Object);

	LaneMeshComponent->AddLocalOffset(FVector(10.0f, 10.0f, 10.0f));


 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALane::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALane::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

