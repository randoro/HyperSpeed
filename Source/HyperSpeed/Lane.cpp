// Fill out your copyright notice in the Description page of Project Settings.

#include "HyperSpeed.h"
#include "Lane.h"


// Sets default values
ALane::ALane()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));

	RootComponent = SceneComponent;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/Geometry/Meshes/1M_Cube.1M_Cube"));
	// Create the mesh component
	LaneMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaneMesh"));
	LaneMeshComponent->AttachTo(RootComponent);
	LaneMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	LaneMeshComponent->SetStaticMesh(ShipMesh.Object);
	LaneMeshComponent->AddLocalTransform(FTransform(FVector(100.0f, 0.0f, 0.0f)));

	// Create the left mesh component
	LeftLaneMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftLaneMesh"));
	//RootComponent = LeftLaneMeshComponent;
	LeftLaneMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	LeftLaneMeshComponent->SetStaticMesh(ShipMesh.Object);
	LeftLaneMeshComponent->AttachTo(RootComponent);
	//SetupOrientation();
	//LeftLaneMeshComponent->SetRelativeLocation(LaneMeshComponent->RelativeLocation);
	//LeftLaneMeshComponent->AddWorldTransform(FTransform(FVector(0.0f, -10.0f, 0.0f)));

	//// Create the right mesh component
	//RightLaneMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightLaneMesh"));
	////RootComponent = RightLaneMeshComponent;
	//RightLaneMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	//RightLaneMeshComponent->SetStaticMesh(ShipMesh.Object);
	//RightLaneMeshComponent->AddWorldTransform(FTransform(FVector(0.0f, 10.0f, 0.0f)));


 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ALane::SetupOrientation()
{
	FVector Position;
	Position.X = 0.0f;
	Position.Y = 0.0f;
	Position.Z = 1000.0f;

	FRotator Rotation;
	Rotation.Yaw = 0.0f;
	Rotation.Pitch = 0.0f;
	Rotation.Roll = 0.0f;

	LeftLaneMeshComponent->SetMobility(EComponentMobility::Movable);
	LeftLaneMeshComponent->SetWorldLocationAndRotation(Position, Rotation);
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

