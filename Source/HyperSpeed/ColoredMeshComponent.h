// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Engine.h"
#include "ColoredMeshComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HYPERSPEED_API UColoredMeshComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Material")
	class UMaterialInterface* GlowMaterial;

	UPROPERTY(VisibleAnywhere, Category = "Material")
	class UMaterialInstanceDynamic* DynamicMaterial;

public:	
	// Sets default values for this component's properties
	UColoredMeshComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
	
};
