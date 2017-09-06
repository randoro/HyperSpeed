// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Engine.h"
#include "ColoredMeshComponent.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EHyperColorEnum : uint8
{
	HC_Yellow 	UMETA(DisplayName = "Yellow"),
	HC_Pink 	UMETA(DisplayName = "Pink"),
	HC_Blue	UMETA(DisplayName = "Blue")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HYPERSPEED_API UColoredMeshComponent : public UActorComponent
{
	GENERATED_BODY()

	void SetMeshColorSettings(EHyperColorEnum newColor);

	UPROPERTY(Category = "Material", VisibleAnywhere)
	class UMaterial* YellowMaterial;

	UPROPERTY(Category = "Material", VisibleAnywhere)
	class UMaterial* PinkMaterial;

	UPROPERTY(Category = "Material", VisibleAnywhere)
	class UMaterial* BlueMaterial;


public:	
	// Sets default values for this component's properties
	UColoredMeshComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;

	virtual void InitializeComponent() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
	EHyperColorEnum CurrentColor;
	
};
