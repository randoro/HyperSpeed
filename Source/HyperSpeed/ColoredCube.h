// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ColoredCube.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EHyperColorEnum : uint8
{
	HC_Yellow 	UMETA(DisplayName = "Yellow"),
	HC_Pink 	UMETA(DisplayName = "Pink"),
	HC_Blue	UMETA(DisplayName = "Blue")
};

UCLASS()
class HYPERSPEED_API AColoredCube : public AActor
{
	GENERATED_BODY()

	/* The mesh component */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* LaneMeshComponent;

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* LaneTrigger;

	UFUNCTION()
	void OnBeginOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnEndOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	void SetMeshColorSettings(EHyperColorEnum newColor);

	class UMaterial* YellowMaterial;

	class UMaterial* PinkMaterial;

	class UMaterial* BlueMaterial;
	
	
public:	
	// Sets default values for this actor's properties
	AColoredCube();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
		EHyperColorEnum CurrentColor;
	
};
