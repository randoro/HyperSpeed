// Fill out your copyright notice in the Description page of Project Settings.

#include "HyperSpeed.h"
#include "ColoredCube.h"
#include "Engine.h"
#include "FlipComponent.h"

// Sets default values
AColoredCube::AColoredCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LaneMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaneMesh"));
	LaneTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerMesh0"));

	const static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/Geometry/Meshes/1M_Cube.1M_Cube"));
	const static ConstructorHelpers::FObjectFinder<UMaterial> YellowMaterialRef(TEXT("Material'/Game/YellowMaterial.YellowMaterial'"));
	const static ConstructorHelpers::FObjectFinder<UMaterial> PinkMaterialRef(TEXT("Material'/Game/PinkMaterial.PinkMaterial'"));
	const static ConstructorHelpers::FObjectFinder<UMaterial> BlueMaterialRef(TEXT("Material'/Game/BlueMaterial.BlueMaterial'"));
	YellowMaterial = YellowMaterialRef.Object;
	PinkMaterial = PinkMaterialRef.Object;
	BlueMaterial = BlueMaterialRef.Object;


	LaneMeshComponent->AttachTo(RootComponent);
	//LaneMeshComponent->SetCollisionProfileName(FName("YellowObject"));
	LaneMeshComponent->SetStaticMesh(ShipMesh.Object);
	//LaneMeshComponent->SetMaterial(0, YellowMaterialRef.Object);

	LaneTrigger->AttachTo(LaneMeshComponent);
	LaneTrigger->OnComponentBeginOverlap.AddDynamic(this, &AColoredCube::OnBeginOverlap);
	LaneTrigger->OnComponentEndOverlap.AddDynamic(this, &AColoredCube::OnEndOverlap);
	LaneTrigger->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	//LaneTrigger->SetCollisionProfileName(FName("ColorTrigger"));

	SetMeshColorSettings(EHyperColorEnum::HC_Yellow);

	this->OnActorHit.AddDynamic(this, &AColoredCube::OnHit);

}

// Called when the game starts or when spawned
void AColoredCube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AColoredCube::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AColoredCube::OnBeginOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->IsA(AWheeledVehicle::StaticClass()))
	{

		UFlipComponent* FlipComp = NULL;

		TArray<UFlipComponent*> Comps;
		OtherActor->GetComponents(Comps);
		for (size_t i = 0; i < Comps.Num(); i++)
		{
			if (Comps[i]->IsA(UFlipComponent::StaticClass()))
			{
				FlipComp = Comps[i];
			}
		}

		if (FlipComp) {

			ECollisionChannel channel = OtherActor->GetRootComponent()->GetCollisionObjectType();

			if (channel == ECollisionChannel::ECC_GameTraceChannel5)
			{
				UE_LOG(LogTemp, Warning, TEXT("Overlap begun with Yellow car"));

				switch (CurrentColor)
				{
				case EHyperColorEnum::HC_Yellow:
					LaneMeshComponent->SetCollisionProfileName(FName("NoCollision"));
					FlipComp->isInsideYellow = true;
					break;
				case EHyperColorEnum::HC_Pink:
					LaneMeshComponent->SetCollisionProfileName(FName("PinkObject"));
					FlipComp->isInsidePink = true;
					break;
				case EHyperColorEnum::HC_Blue:
					LaneMeshComponent->SetCollisionProfileName(FName("BlueObject"));
					FlipComp->isInsideBlue = true;
					break;
				default:
					break;
				}
			}
			else if (channel == ECollisionChannel::ECC_GameTraceChannel6)
			{
				UE_LOG(LogTemp, Warning, TEXT("Overlap begun with Pink car"));

				switch (CurrentColor)
				{
				case EHyperColorEnum::HC_Yellow:
					LaneMeshComponent->SetCollisionProfileName(FName("YellowObject"));
					FlipComp->isInsideYellow = true;
					break;
				case EHyperColorEnum::HC_Pink:
					LaneMeshComponent->SetCollisionProfileName(FName("NoCollision"));
					FlipComp->isInsidePink = true;
					break;
				case EHyperColorEnum::HC_Blue:
					LaneMeshComponent->SetCollisionProfileName(FName("BlueObject"));
					FlipComp->isInsideBlue = true;
					break;
				default:
					break;
				}
			}
			else if (channel == ECollisionChannel::ECC_GameTraceChannel7)
			{
				UE_LOG(LogTemp, Warning, TEXT("Overlap begun with Blue car"));
				switch (CurrentColor)
				{
				case EHyperColorEnum::HC_Yellow:
					LaneMeshComponent->SetCollisionProfileName(FName("YellowObject"));
					FlipComp->isInsideYellow = true;
					break;
				case EHyperColorEnum::HC_Pink:
					LaneMeshComponent->SetCollisionProfileName(FName("PinkObject"));
					FlipComp->isInsidePink = true;
					break;
				case EHyperColorEnum::HC_Blue:
					LaneMeshComponent->SetCollisionProfileName(FName("NoCollision"));
					FlipComp->isInsideBlue = true;
					break;
				default:
					break;
				}
			}
		}
	}
}


void AColoredCube::OnEndOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(AWheeledVehicle::StaticClass()))
	{

		UFlipComponent* FlipComp = NULL;

		TArray<UFlipComponent*> Comps;
		OtherActor->GetComponents(Comps);
		for (size_t i = 0; i < Comps.Num(); i++)
		{
			if (Comps[i]->IsA(UFlipComponent::StaticClass()))
			{
				FlipComp = Comps[i];
			}
		}
		if (FlipComp) {

			ECollisionChannel channel = OtherActor->GetRootComponent()->GetCollisionObjectType();

			if (channel == ECollisionChannel::ECC_GameTraceChannel5 || channel == ECollisionChannel::ECC_GameTraceChannel6 || channel == ECollisionChannel::ECC_GameTraceChannel7)
			{
				UE_LOG(LogTemp, Warning, TEXT("Overlap ended with car"));
				switch (CurrentColor)
				{
				case EHyperColorEnum::HC_Yellow:
					LaneMeshComponent->SetCollisionProfileName(FName("YellowObject"));
					FlipComp->isInsideYellow = false;
					break;
				case EHyperColorEnum::HC_Pink:
					LaneMeshComponent->SetCollisionProfileName(FName("PinkObject"));
					FlipComp->isInsidePink = false;
					break;
				case EHyperColorEnum::HC_Blue:
					LaneMeshComponent->SetCollisionProfileName(FName("BlueObject"));
					FlipComp->isInsideBlue = false;
					break;
				default:
					break;
				}
			}
		}
	}

}

void AColoredCube::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Object Got hit!"));
}

void AColoredCube::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	Super::PostEditChangeProperty(e);

	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AColoredCube, CurrentColor))
	{
		//various uproperty tricks
		UNumericProperty* EnumProperty = Cast<UNumericProperty>(e.Property);
		FString StringValue = EnumProperty->GetNumericPropertyValueToString(&CurrentColor);
		int32 IntValue = FCString::Atoi(*StringValue);
		EHyperColorEnum EnumValue = static_cast<EHyperColorEnum>(IntValue);
		UE_LOG(LogTemp, Warning, TEXT("Current Color Changed in Editor!"));
		SetMeshColorSettings(EnumValue);

	}

}

void AColoredCube::SetMeshColorSettings(EHyperColorEnum newColor)
{
	
			switch (newColor)
			{
			case EHyperColorEnum::HC_Yellow:
				LaneMeshComponent->SetCollisionProfileName(FName("YellowObject"));
				LaneTrigger->SetCollisionProfileName(FName("ColorTrigger"));
				LaneMeshComponent->bGenerateOverlapEvents = true;
				//RecreatePhysicsState();

				LaneMeshComponent->SetMaterial(0, YellowMaterial);
				MarkComponentsRenderStateDirty();
				//MarkRenderStateDirty();
				break;
			case EHyperColorEnum::HC_Pink:
				LaneMeshComponent->SetCollisionProfileName(FName("PinkObject"));
				LaneTrigger->SetCollisionProfileName(FName("ColorTrigger"));
				LaneMeshComponent->bGenerateOverlapEvents = true;
				//RecreatePhysicsState();

				LaneMeshComponent->SetMaterial(0, PinkMaterial);
				MarkComponentsRenderStateDirty();
				//MarkRenderStateDirty();
				break;
			case EHyperColorEnum::HC_Blue:
				LaneMeshComponent->SetCollisionProfileName(FName("BlueObject"));
				LaneTrigger->SetCollisionProfileName(FName("ColorTrigger"));
				LaneMeshComponent->bGenerateOverlapEvents = true;
				//RecreatePhysicsState();

				LaneMeshComponent->SetMaterial(0, BlueMaterial);
				MarkComponentsRenderStateDirty();
				//MarkRenderStateDirty();
				break;
			default:
				break;
			}
}

