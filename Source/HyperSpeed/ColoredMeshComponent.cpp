// Fill out your copyright notice in the Description page of Project Settings.

#include "HyperSpeed.h"
#include "ColoredMeshComponent.h"


// Sets default values for this component's properties
UColoredMeshComponent::UColoredMeshComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	//AActor* actor = Cast<AActor>(GetOwner());
	//if (actor)
	//{
	//	//is actor
	//	UStaticMeshComponent* mesh = Cast<UStaticMeshComponent>(actor->GetRootComponent());
	//	if (mesh) 
	//	{
	//		//has mesh
	//		//GlowMaterial = UMaterialInstanceDynamic::Create(mesh->GetMaterial(0), this);
	//		if (GlowMaterial) 
	//		{
	//			mesh->SetMaterial(0, GlowMaterial);
	//			
	//		}
	//		//material->Set**ParameterValue(FName(TEXT("Name you called parameter")), somethingParameterType);
	//	}
	//}


	// ...
}


// Called when the game starts
void UColoredMeshComponent::BeginPlay()
{
	Super::BeginPlay();

	//AActor* actor = Cast<AActor>(GetOwner());
	//if (actor)
	//{
	//	//is actor
	//	UStaticMeshComponent* mesh = Cast<UStaticMeshComponent>(actor->GetRootComponent());
	//	if (mesh)
	//	{
	//		if (GlowMaterial) {
	//			//has mesh
	//			DynamicMaterial = UMaterialInstanceDynamic::Create(GlowMaterial, this);
	//			if (DynamicMaterial)
	//			{
	//				FLinearColor PinkColor = FLinearColor(1.0f, 0.0f, 1.0f);
	//				FLinearColor PinkWhiteColor = FLinearColor(1.0f, 0.5f, 1.0f);
	//				DynamicMaterial->SetVectorParameterValue(FName(TEXT("BaseColor")), PinkColor);
	//				DynamicMaterial->SetVectorParameterValue(FName(TEXT("EmissiveColor")), PinkWhiteColor);
	//				DynamicMaterial->SetScalarParameterValue(FName(TEXT("Opacity")), 1.0f);
	//				DynamicMaterial->SetScalarParameterValue(FName(TEXT("EmissiveStrength")), 1.0f);
	//				mesh->SetMaterial(0, DynamicMaterial);
	//				MarkRenderStateDirty();

	//			}
	//		}
	//		//material->Set**ParameterValue(FName(TEXT("Name you called parameter")), somethingParameterType);
	//	}
	//}

	// ...
	
}


// Called every frame
void UColoredMeshComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

