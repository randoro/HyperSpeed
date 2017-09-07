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
		}
	}

	TArray<UWheeledVehicleMovementComponent4W*> Comps2;
	actor->GetComponents(Comps2);
	for (size_t i = 0; i < Comps2.Num(); i++)
	{
		if (Comps2[i]->IsA(UWheeledVehicleMovementComponent4W::StaticClass()))
		{
			VehicleMovementComponent = Comps2[i];
		}
	}

	TArray<UBoxComponent*> Comps3;
	actor->GetComponents(Comps3);
	for (size_t i = 0; i < Comps3.Num(); i++)
	{
		if (Comps3[i]->IsA(UBoxComponent::StaticClass()))
		{
			BoxMeshComponent = Comps3[i];

		}
	}
	
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
	if (!isInsideYellow && !isInsidePink && !isInsideBlue) {

		if (AxisValue == 0.0f)
		{


			if (color != 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("Car Switched to Yellow"));
				//Switch Color, collision and material color
				color = 0;
				ChangeColorCollection(color);
				CarMeshComponent->SetCollisionProfileName(FName("YellowVehicle"));

			}
		}
		else if (AxisValue < 0.0f) {

			if (color != 1)
			{
				UE_LOG(LogTemp, Warning, TEXT("Car Switched to Pink"));
				color = 1;
				ChangeColorCollection(color);
				CarMeshComponent->SetCollisionProfileName(FName("PinkVehicle"));

			}
		}
		else if (AxisValue > 0.0f) {


			if (color != 2)
			{
				UE_LOG(LogTemp, Warning, TEXT("Car Switched to Blue"));
				color = 2;
				ChangeColorCollection(color);
				CarMeshComponent->SetCollisionProfileName(FName("BlueVehicle"));

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

	FLinearColor YellowColor = FLinearColor(0.745f, 0.407f, 0.0f);
	FLinearColor PinkColor = FLinearColor(0.888f, 0.032f, 0.631f);
	FLinearColor BlueColor = FLinearColor(0.0f, 0.434f, 0.888f);

	switch (CheckColor)
	{
	case 0:
		UKismetMaterialLibrary::SetVectorParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("CarColor")), YellowColor);
		
		UKismetMaterialLibrary::SetVectorParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("YellowBaseColor")), YellowColor);
		UKismetMaterialLibrary::SetVectorParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("YellowEmissiveColor")), YellowColor);
		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("YellowOpacity")), 0.5f);
		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("YellowEmissiveStrength")), 0.5f);

		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("PinkOpacity")), 1.0f);
		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("PinkEmissiveStrength")), 5.0f);
		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("BlueOpacity")), 1.0f);
		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("BlueEmissiveStrength")), 5.0f);

		break;
	case 1:
		UKismetMaterialLibrary::SetVectorParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("CarColor")), PinkColor);
		
		UKismetMaterialLibrary::SetVectorParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("PinkBaseColor")), PinkColor);
		UKismetMaterialLibrary::SetVectorParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("PinkEmissiveColor")), PinkColor);
		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("PinkOpacity")), 0.5f);
		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("PinkEmissiveStrength")), 0.5f);

		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("YellowOpacity")), 1.0f);
		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("YellowEmissiveStrength")), 5.0f);
		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("BlueOpacity")), 1.0f);
		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("BlueEmissiveStrength")), 5.0f);
		break;
	case 2:
		UKismetMaterialLibrary::SetVectorParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("CarColor")), BlueColor);

		UKismetMaterialLibrary::SetVectorParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("BlueBaseColor")), BlueColor);
		UKismetMaterialLibrary::SetVectorParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("BlueEmissiveColor")), BlueColor);
		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("BlueOpacity")), 0.5f);
		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("BlueEmissiveStrength")), 0.5f);


		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("YellowOpacity")), 1.0f);
		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("YellowEmissiveStrength")), 5.0f);
		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("PinkOpacity")), 1.0f);
		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MyParameterCollection, FName(TEXT("PinkEmissiveStrength")), 5.0f);
		break;
	default:
		break;
	}
	
}

