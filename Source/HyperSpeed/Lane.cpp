// Fill out your copyright notice in the Description page of Project Settings.

#include "HyperSpeed.h"
#include "HyperSpeedPawn.h"
#include "Lane.h"


// Sets default values
ALane::ALane()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	LaneMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaneMesh"));
	LeftLaneMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftLaneMesh"));
	RightLaneMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightLaneMesh"));
	LaneTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerMesh0"));

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

	LaneTrigger->AttachTo(RootComponent);
	LaneTrigger->OnComponentBeginOverlap.AddDynamic(this, &ALane::OnBeginOverlap);
	LaneTrigger->OnComponentEndOverlap.AddDynamic(this, &ALane::OnEndOverlap);

}

void ALane::SetupOrientation()
{
	FRotator NoRotation = FRotator(0.0f, 0.0f, 0.0f);
	float TrackLength = 30.0f;

	//Scale
	FVector LaneScale;
	LaneScale.X = TrackLength;
	LaneScale.Y = 12.0f;
	LaneScale.Z = 1.0f;

	FVector LeftLaneScale;
	LeftLaneScale.X = TrackLength;
	LeftLaneScale.Y = 0.2f;
	LeftLaneScale.Z = 1.0f;

	FVector RightLaneScale;
	RightLaneScale.X = TrackLength;
	RightLaneScale.Y = 0.2f;
	RightLaneScale.Z = 1.0f;



	//Position
	FVector LeftLanePosition;
	LeftLanePosition.X = 0.0f;
	LeftLanePosition.Y = -590.0f;
	LeftLanePosition.Z = 100.0f;

	FVector RightLanePosition;
	RightLanePosition.X = 0.0f;
	RightLanePosition.Y = 590.0f;
	RightLanePosition.Z = 100.0f;

	//Scale
	LaneMeshComponent->SetWorldScale3D(LaneScale);
	
	//Position
	LeftLaneMeshComponent->AddLocalTransform(FTransform(NoRotation, LeftLanePosition, LeftLaneScale));
	RightLaneMeshComponent->AddLocalTransform(FTransform(NoRotation, RightLanePosition, RightLaneScale));

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

void ALane::OnBeginOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->IsA(AHyperSpeedPawn::StaticClass()))
	{
		LaneMeshComponent->SetVisibility(false);
		//AStarWingGameMode* gm = (AStarWingGameMode*)GetWorld()->GetAuthGameMode();
		//gm->AddTime(3000);
	}
}


void ALane::OnEndOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	LaneMeshComponent->SetVisibility(true);
}