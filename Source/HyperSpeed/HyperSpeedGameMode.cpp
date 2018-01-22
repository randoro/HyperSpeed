// Fill out your copyright notice in the Description page of Project Settings.

#include "HyperSpeed.h"
#include "HyperSpeedGameMode.h"

AHyperSpeedGameMode::AHyperSpeedGameMode()
{
}

void AHyperSpeedGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (HUDWidgetClass)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

void AHyperSpeedGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Time--;

	if (Time < 0) 
	{
		UGameplayStatics::OpenLevel(GetWorld(), "MainMenuLevel");
	}
}

int32 AHyperSpeedGameMode::GetTime()
{
	return Time;
}

void AHyperSpeedGameMode::SetTime(int32 NewTime)
{
	Time = NewTime;
}


