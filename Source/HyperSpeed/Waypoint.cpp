// Fill out your copyright notice in the Description page of Project Settings.

#include "HyperSpeed.h"
#include "Waypoint.h"
#include "Route.h"


// Sets default values
AWaypoint::AWaypoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	WaypointMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WaypointMesh"));
	WaypointTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerMesh0"));

	const static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/Geometry/Meshes/1M_Cube.1M_Cube"));

	//Fill SubObjects
	WaypointMeshComponent->SetStaticMesh(ShipMesh.Object);
	WaypointMeshComponent->SetHiddenInGame(true);
	WaypointMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	WaypointTrigger->OnComponentBeginOverlap.AddDynamic(this, &AWaypoint::OnBeginOverlap);
	WaypointTrigger->OnComponentEndOverlap.AddDynamic(this, &AWaypoint::OnEndOverlap);
	WaypointTrigger->SetBoxExtent(FVector(1500.0f, 1500.0f, 1500.0f));
	WaypointTrigger->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	WaypointTrigger->SetCollisionProfileName(TEXT("Trigger"));

	//Attach SubObjects
	WaypointMeshComponent->AttachTo(RootComponent);
	WaypointTrigger->AttachTo(WaypointMeshComponent);


}

// Called when the game starts or when spawned
void AWaypoint::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AWaypoint::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AWaypoint::SetRoute(ARoute* CurrentRoute)
{
	Route = CurrentRoute;

}


void AWaypoint::OnBeginOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Entered Waypoint X:%f Y:%f Z:%f"), 0.0f, 0.0f, 0.0f);
	if (Route != NULL) {
		AActor* Sel = Route->Selected;
		if (RootComponent->GetAttachmentRootActor() == Sel) {
			UE_LOG(LogTemp, Warning, TEXT("Entered Selected Waypoint X:%f Y:%f Z:%f"), 0.0f, 0.0f, 0.0f);
			Route->SelectNext();
		}
	}
	//if (OtherActor->IsA(AWheeledVehicle::StaticClass()))
	//{
	//	AWheeledVehicle* otherA = Cast<AWheeledVehicle>(OtherActor);

	//	TArray<USkeletalMeshComponent*> Comps;
	//	OtherActor->GetComponents(Comps);
	//	for (size_t i = 0; i < Comps.Num(); i++)
	//	{

	//		if (Comps[i]->IsA(USkeletalMeshComponent::StaticClass()))
	//		{
	//			USkeletalMeshComponent* otherV = Comps[i];

	//			UE_LOG(LogTemp, Warning, TEXT("Forward FVector X:%f Y:%f Z:%f"), RootComponent->GetForwardVector().X, RootComponent->GetForwardVector().Y, RootComponent->GetForwardVector().Z);
	//			otherV->SetPhysicsLinearVelocity(otherV->GetPhysicsLinearVelocity() + (500.0f * RootComponent->GetForwardVector())); //Cap to max speed
	//			
	//			UE_LOG(LogTemp, Warning, TEXT("Enter and gain 10% Velocity now its FVector X:%f Y:%f Z:%f"), otherV->GetPhysicsLinearVelocity().X, otherV->GetPhysicsLinearVelocity().Y, otherV->GetPhysicsLinearVelocity().Z);

	//		}
	//		//do stuff with FoundComp
	//	}


	//}
}


void AWaypoint::OnEndOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}
