// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Engine.h"
#include "FlipComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HYPERSPEED_API UFlipComponent : public UActorComponent
{
	GENERATED_BODY()

	/* The mesh component */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* CarMeshComponent;

	
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UWheeledVehicleMovementComponent4W* VehicleMovementComponent;

	
	UPROPERTY(Category = "Jumping", EditAnywhere)
	float JumpHeight;

	UPROPERTY(Category = "Jumping", EditAnywhere)
		float JumpPercentageIncreaseFromVelocity;

	UPROPERTY(Category = "Color", EditAnywhere)
		INT32 color;

public:	
	// Sets default values for this component's properties
	UFlipComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	
	UFUNCTION(BlueprintCallable, Category = "Jumping")
	void DoJump(bool isOnGround);

	UFUNCTION(BlueprintCallable, Category = "Color")
		void ChangeColor(float AxisValue);

};
