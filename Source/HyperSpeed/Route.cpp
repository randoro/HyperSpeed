// Fill out your copyright notice in the Description page of Project Settings.

#include "HyperSpeed.h"
#include "Route.h"


// Sets default values
ARoute::ARoute()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARoute::BeginPlay()
{
	Super::BeginPlay();

	APawn* myCharacter = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	AActor* OtherCharacter = Cast<AActor>(myCharacter);


	
		/*TArray<UStaticMeshComponent*> StaticComps;
		StaticComps = OtherCharacter->GetComponentsByTag(UStaticMeshComponent::StaticClass(), FName("Arrow"));
		for (size_t i = 0; i < StaticComps.Num(); i++)
		{
			Arrow = StaticComps[i];
		}
		if (Arrow != NULL)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found Arrow X:%f Y:%f Z:%f"), 0.0f, 0.0f, 0.0f);
		}*/
	

	/*TArray<USkeletalMeshComponent*> Comps;
	OtherCharacter->GetComponents(Comps);
	for (size_t i = 0; i < Comps.Num(); i++)
	{
		if (Comps[i]->IsA(USkeletalMeshComponent::StaticClass()))
		{
			CarMeshComponent = Comps[i];
		}
	}*/

	TArray<USkeletalMeshComponent*> StaticComps;
	OtherCharacter->GetComponents(StaticComps);
	for (size_t i = 0; i < StaticComps.Num(); i++)
	{
		if (StaticComps[i]->IsA(USkeletalMeshComponent::StaticClass()))
		{
			Arrow = Cast<UStaticMeshComponent>(StaticComps[i]->GetChildComponent(0)->GetChildComponent(0)->GetChildComponent(0));
			if (Arrow != NULL) 
			{
				UE_LOG(LogTemp, Warning, TEXT("Found Arrow X:%f Y:%f Z:%f"), 0.0f, 0.0f, 0.0f);
			}
		}
	}
}

// Called every frame
void ARoute::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
	if (Waypoints.Num() != 0)
	{
		Selected = Waypoints[0];
		Arrow->SetWorldRotation(FRotationMatrix::MakeFromX(Selected->GetActorLocation() - Arrow->GetAttachmentRootActor()->GetActorLocation()).Rotator());
	}

}

