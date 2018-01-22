// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "HyperSpeedGameMode.h"
#include "Route.generated.h"

UCLASS()
class HYPERSPEED_API ARoute : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<AActor*> Waypoints;

	int selectedIndex;
	int clearedPoints;

	

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Arrow;

	UPROPERTY(EditAnywhere)
	AHyperSpeedGameMode* GameMode;
	
public:	
	// Sets default values for this actor's properties
	ARoute();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
	AActor* Selected;

	void SelectNext();
	
};
