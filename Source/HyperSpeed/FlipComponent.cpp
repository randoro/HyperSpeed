// Fill out your copyright notice in the Description page of Project Settings.

#include "HyperSpeed.h"
#include "FlipComponent.h"
#include "Runtime/Engine/Classes/Kismet/KismetMaterialLibrary.h"


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

	TArray<UWheeledVehicleMovementComponent4W*> Comps2;
	actor->GetComponents(Comps2);
	for (size_t i = 0; i < Comps2.Num(); i++)
	{
		if (Comps2[i]->IsA(UWheeledVehicleMovementComponent4W::StaticClass()))
		{
			VehicleMovementComponent = Comps2[i];
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

void UFlipComponent::DoJump(bool isOnGround) {
	if (isOnGround) {
		FVector vel = CarMeshComponent->GetPhysicsLinearVelocity();
		if ((vel.X < 100 && vel.X > -100) && (vel.Y < 100 && vel.Y > -100) && (vel.Z < 1000 && vel.Z > -100))
		{
			vel.X += 50;
			vel.Y += 50;
			vel.Z += JumpHeight;
		}
		else 
		{
			
			vel.Z += JumpHeight + JumpPercentageIncreaseFromVelocity * vel.Size();
		}
		CarMeshComponent->SetPhysicsLinearVelocity(vel);
	}
}


void UFlipComponent::ChangeColor(float AxisValue)
{
	TArray<AActor*> CraftingActors;
	CarMeshComponent->GetOverlappingActors(CraftingActors);
	bool isInsidePink = false;
	bool isInsideBlue = false;
	bool isInsidePurple = false;
	for (AActor* Actor : CraftingActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor detected!"));

		ECollisionChannel channel = Actor->GetRootComponent()->GetCollisionObjectType();

		if (channel == ECollisionChannel::ECC_GameTraceChannel2)
		{
			isInsidePink = true;
			UE_LOG(LogTemp, Warning, TEXT("Pink: {0}"), isInsidePink);
		}
		else if (channel == ECollisionChannel::ECC_GameTraceChannel3)
		{
			isInsideBlue = true;
			UE_LOG(LogTemp, Warning, TEXT("Blue: {0}"), isInsideBlue);
		}
		else if (channel == ECollisionChannel::ECC_GameTraceChannel4)
		{
			isInsidePurple = true;
			UE_LOG(LogTemp, Warning, TEXT("Purple: {0}"), isInsidePurple);
		}
	}





	if (AxisValue == 0.0f) 
	{
		if (!isInsidePurple) {
			
			if (color != 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("Car Switched to Purple"));
				//Switch Color, collision and material color
				color = 0;
				ChangeColorCollection(color);
				CarMeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel7);
				CarMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Overlap);
				CarMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Overlap);
				CarMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel4, ECollisionResponse::ECR_Block);
				CarMeshComponent->SetNotifyRigidBodyCollision(true);
				RecreatePhysicsState();
			}
		}
	}
	else if (AxisValue < 0.0f) {
		if (!isInsidePink) {
			if (color != 1)
			{
				UE_LOG(LogTemp, Warning, TEXT("Car Switched to Pink"));
				color = 1;
				ChangeColorCollection(color);
				CarMeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel5);
				CarMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Block);
				CarMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Overlap);
				CarMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel4, ECollisionResponse::ECR_Overlap);
				CarMeshComponent->SetNotifyRigidBodyCollision(true);
				RecreatePhysicsState();
			}
		}
	}
	else if (AxisValue > 0.0f) {
		if (!isInsideBlue) {
			
			if (color != 2)
			{
				UE_LOG(LogTemp, Warning, TEXT("Car Switched to Blue"));
				color = 2;
				ChangeColorCollection(color);
				CarMeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel6);
				CarMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Overlap);
				CarMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Block);
				CarMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel4, ECollisionResponse::ECR_Overlap);
				CarMeshComponent->SetNotifyRigidBodyCollision(true);
				RecreatePhysicsState();
			}
		}
	}
	
}

void UFlipComponent::ChangeColorCollection(int CheckColor)
{
	if (!MyParameterCollection)
	{
		MyParameterCollection = LoadObject<UMaterialParameterCollection>(NULL, TEXT("MaterialParameterCollection'/Game/ColorCode.ColorCode'"), NULL, LOAD_None, NULL);
	}

	FLinearColor PurpleColor = FLinearColor(0.415319f, 0.0f, 0.74f);
	FLinearColor PinkColor = FLinearColor(0.887923f, 0.031896f, 0.630757f);
	FLinearColor BlueColor = FLinearColor(0.0f, 0.434154f, 0.887923f);

	switch (CheckColor)
	{
	case 0:
		
		
		UKismetMaterialLibrary::SetVectorParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("BaseColor")), PurpleColor);
		UKismetMaterialLibrary::SetVectorParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("EmissiveColor")), PurpleColor);

		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("Opacity")), 1.0f);
		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("EmissiveStrength")), 10.0f);
		break;
	case 1:
		
		UKismetMaterialLibrary::SetVectorParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("BaseColor")), PinkColor);
		UKismetMaterialLibrary::SetVectorParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("EmissiveColor")), PinkColor);

		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("Opacity")), 1.0f);
		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("EmissiveStrength")), 10.0f);
		break;
	case 2:
		UKismetMaterialLibrary::SetVectorParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("BaseColor")), BlueColor);
		UKismetMaterialLibrary::SetVectorParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("EmissiveColor")), BlueColor);

		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("Opacity")), 1.0f);
		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("EmissiveStrength")), 10.0f);
		break;
	default:
		break;
	}
	
}

