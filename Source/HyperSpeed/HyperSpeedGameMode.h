// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "HyperSpeedGameMode.generated.h"

/**
 * 
 */
UCLASS()
class AHyperSpeedGameMode : public AGameMode
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY()
	class UUserWidget* CurrentWidget;

	UPROPERTY(VisibleAnywhere)
		int32 Time = 2000;

public:
	AHyperSpeedGameMode();

	void BeginPlay();

	void Tick(float DeltaTime);

	UFUNCTION(BlueprintPure, Category = "Time")
	int32 GetTime();

	UFUNCTION(Category = "Time")
		void SetTime(int32 NewTime);
	
};
