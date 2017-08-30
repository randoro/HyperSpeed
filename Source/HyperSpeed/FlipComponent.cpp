// Fill out your copyright notice in the Description page of Project Settings.

#include "HyperSpeed.h"
#include "FlipComponent.h"


// Sets default values for this component's properties
UFlipComponent::UFlipComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UFlipComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* actor = GetOwner();

	TArray<USkeletalMeshComponent*> Comps;
	actor->GetComponents(Comps);
	for (size_t i = 0; i < Comps.Num(); i++)
	{
		if (Comps[i]->IsA(USkeletalMeshComponent::StaticClass()))
		{
			CarMeshComponent = Comps[i];
			/*FRotator SkellRotation = CarMeshComponent->GetComponentRotation();
			SkellRotation.Roll = 0.0f;
			SkellRotation.Pitch = 0.0f;
			SkellRotation.Yaw = 0.0f;

			CarMeshComponent->SetAllPhysicsRotation(SkellRotation);*/

		}
	}

	
	// ...
	
}


// Called every frame
void UFlipComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	FVector vel = CarMeshComponent->GetPhysicsLinearVelocity();
	if ((vel.X < 100 && vel.X > -100) && (vel.Y < 100 && vel.Y > -100) && (vel.Z < 1000 && vel.Z > -100)) 
	{
		//It's too slow.
		FRotator SkellRotation = CarMeshComponent->GetComponentRotation();
		if ((SkellRotation.Roll > 80 || SkellRotation.Roll < -80) || (SkellRotation.Pitch > 80 || SkellRotation.Pitch < -80)) 
		{
			SkellRotation.Roll = 0.0f;
			SkellRotation.Pitch = 0.0f;
			vel.X += 50;
			vel.Y += 50;
			vel.Z += 1000;
			CarMeshComponent->SetAllPhysicsRotation(SkellRotation);
			CarMeshComponent->SetPhysicsLinearVelocity(vel);
		}
	}

//	FRotator SkellRotation = CarMeshComponent->GetComponentRotation();
//	/*SkellRotation.Roll += 0.0f;
//	SkellRotation.Pitch += 1.0f;
//	SkellRotation.Yaw += 0.0f;
//	FQuat quat = SkellRotation.Quaternion();
//	quat.X
//*/
//	CarMeshComponent->SetAllPhysicsRotation(SkellRotation);

	/*AActor* actor = GetOwner();
	FRotator ActorRotation = actor->GetActorRotation();
	ActorRotation.Pitch += 5.0f;
	actor->SetActorRotation(ActorRotation);*/
}

