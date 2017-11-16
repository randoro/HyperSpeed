// Fill out your copyright notice in the Description page of Project Settings.

#include "HyperSpeed.h"
#include "Booster.h"
#include "Engine.h"


// Sets default values
ABooster::ABooster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Static refs
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ArrowMeshRef(TEXT("/Game/Arrow.Arrow"));



	//Create SubObjects
	ArrowMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowMesh"));
	BoostTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerMesh0"));

	//Fill SubObjects
	ArrowMeshComponent->SetStaticMesh(ArrowMeshRef.Object);
	ArrowMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BoostTrigger->OnComponentBeginOverlap.AddDynamic(this, &ABooster::OnBeginOverlap);
	BoostTrigger->OnComponentEndOverlap.AddDynamic(this, &ABooster::OnEndOverlap);
	BoostTrigger->SetBoxExtent(FVector(300.0f, 200.0f, 300.0f));
	BoostTrigger->SetRelativeLocation(FVector(-150.0f, 75.0f, 0.0f));
	BoostTrigger->SetCollisionProfileName(TEXT("Trigger"));

	//Attach SubObjects
	ArrowMeshComponent->AttachTo(RootComponent);
	BoostTrigger->AttachTo(ArrowMeshComponent);
	

}

// Called when the game starts or when spawned
void ABooster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABooster::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ABooster::OnBeginOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->IsA(AWheeledVehicle::StaticClass()))
	{
		AWheeledVehicle* otherA = Cast<AWheeledVehicle>(OtherActor);

		TArray<USkeletalMeshComponent*> Comps;
		OtherActor->GetComponents(Comps);
		for (size_t i = 0; i < Comps.Num(); i++)
		{

			if (Comps[i]->IsA(USkeletalMeshComponent::StaticClass()))
			{
				USkeletalMeshComponent* otherV = Comps[i];

				UE_LOG(LogTemp, Warning, TEXT("Forward FVector X:%f Y:%f Z:%f"), RootComponent->GetForwardVector().X, RootComponent->GetForwardVector().Y, RootComponent->GetForwardVector().Z);
				otherV->SetPhysicsLinearVelocity(otherV->GetPhysicsLinearVelocity() + (500.0f * RootComponent->GetForwardVector())); //Cap to max speed
				//FVector vel = otherV->Velocity;
				//otherV->MaxEngineRPM = 32000.0f;
				UE_LOG(LogTemp, Warning, TEXT("Enter and gain 10% Velocity now its FVector X:%f Y:%f Z:%f"), otherV->GetPhysicsLinearVelocity().X, otherV->GetPhysicsLinearVelocity().Y, otherV->GetPhysicsLinearVelocity().Z);
				
			}
			//do stuff with FoundComp
		}

		//TArray<UWheeledVehicleMovementComponent*> Comps;
		//OtherActor->GetComponents(Comps);
		//for (size_t i = 0; i < Comps.Num(); i++)
		//{

		//	if (Comps[i]->IsA(UWheeledVehicleMovementComponent::StaticClass()))
		//	{
		//		UWheeledVehicleMovementComponent* otherV = Comps[i];
		//		FVector vel = otherV->Velocity;
		//		otherV->MaxEngineRPM = 32000.0f;
		//		UE_LOG(LogTemp, Warning, TEXT("Enter and gain MaxEngineRPM: %f"), otherV->MaxEngineRPM);

		//	}
		//	//do stuff with FoundComp
		//}

		
	}
}


void ABooster::OnEndOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//if (OtherActor->IsA(AWheeledVehicle::StaticClass()))
	//{
	//	AWheeledVehicle* otherA = Cast<AWheeledVehicle>(OtherActor);

	//	TArray<UWheeledVehicleMovementComponent*> Comps;
	//	OtherActor->GetComponents(Comps);
	//	for (size_t i = 0; i < Comps.Num(); i++)
	//	{

	//		if (Comps[i]->IsA(UWheeledVehicleMovementComponent::StaticClass()))
	//		{
	//			UWheeledVehicleMovementComponent* otherV = Comps[i];
	//			FVector vel = otherV->Velocity;
	//			otherV->MaxEngineRPM = 4000.0f;
	//			UE_LOG(LogTemp, Warning, TEXT("Exit and gain MaxEngineRPM: %f"), otherV->MaxEngineRPM);

	//		}
	//		//do stuff with FoundComp
	//	}
	//}
}