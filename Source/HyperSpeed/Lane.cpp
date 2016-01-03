// Fill out your copyright notice in the Description page of Project Settings.

#include "HyperSpeed.h"
#include "Lane.h"


// Sets default values
ALane::ALane()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	LaneMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaneMesh"));
	LeftLaneMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftLaneMesh"));
	RightLaneMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightLaneMesh"));

	InitializeComponents();

	SetupOrientation();


 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ALane::InitializeComponents()
{
	//Create static texture
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/Geometry/Meshes/1M_Cube.1M_Cube"));

	//SceneComponent
	RootComponent = SceneComponent;

	//Middle
	LaneMeshComponent->AttachTo(RootComponent);
	LaneMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	LaneMeshComponent->SetStaticMesh(ShipMesh.Object);

	//Left
	LeftLaneMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	LeftLaneMeshComponent->SetStaticMesh(ShipMesh.Object);
	LeftLaneMeshComponent->AttachTo(RootComponent);

	//Right
	RightLaneMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	RightLaneMeshComponent->SetStaticMesh(ShipMesh.Object);
	RightLaneMeshComponent->AttachTo(RootComponent);



}

void ALane::SetupOrientation()
{

	FVector LaneScale;
	LaneScale.X = 1.0f;
	LaneScale.Y = 12.0f;
	LaneScale.Z = 1.0f;



	//Position
	FVector LeftLanePosition;
	LeftLanePosition.X = 0.0f;
	LeftLanePosition.Y = 100.0f;
	LeftLanePosition.Z = 10.0f;

	FVector RightLanePosition;
	RightLanePosition.X = 0.0f;
	RightLanePosition.Y = -100.0f;
	RightLanePosition.Z = 10.0f;

	//Scale
	LaneMeshComponent->SetRelativeScale3D(LaneScale);
	//Position
	LeftLaneMeshComponent->AddLocalTransform(FTransform(LeftLanePosition));
	RightLaneMeshComponent->AddLocalTransform(FTransform(RightLanePosition));

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

