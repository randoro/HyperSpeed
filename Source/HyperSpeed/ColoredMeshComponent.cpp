// Fill out your copyright notice in the Description page of Project Settings.

#include "HyperSpeed.h"
#include "ColoredMeshComponent.h"

//template <typename EnumType>
//static FORCEINLINE EnumType GetEnumValueFromString(const FString& EnumName, const FString& String)
//{
//	UEnum* Enum = FindObject<UEnum>(ANY_PACKAGE, *EnumName, true);
//	if (!Enum)
//	{
//		return EnumType(0);
//	}
//	return (EnumType)Enum->FindEnumIndex(FName(*String));
//}

// Sets default values for this component's properties
UColoredMeshComponent::UColoredMeshComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	/*const static ConstructorHelpers::FObjectFinder<UMaterial> YellowMaterialRef(TEXT("Material'/Game/YellowMaterial.YellowMaterial'"));
	const static ConstructorHelpers::FObjectFinder<UMaterial> PinkMaterialRef(TEXT("Material'/Game/PinkMaterial.PinkMaterial'"));
	const static ConstructorHelpers::FObjectFinder<UMaterial> BlueMaterialRef(TEXT("Material'/Game/BlueMaterial.BlueMaterial'"));
	YellowMaterial = YellowMaterialRef.Object;
	PinkMaterial = PinkMaterialRef.Object;
	BlueMaterial = BlueMaterialRef.Object;*/

	//SetMeshColorSettings(EHyperColorEnum::HC_Yellow);
}

void UColoredMeshComponent::InitializeComponent()
{
	Super::InitializeComponent();

	//SetMeshColorSettings(EHyperColorEnum::HC_Yellow);
}


// Called when the game starts
void UColoredMeshComponent::BeginPlay()
{
	Super::BeginPlay();

	//SetMeshColorSettings(CurrentColor);

}


// Called every frame
void UColoredMeshComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UColoredMeshComponent::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	Super::PostEditChangeProperty(e);

	

	//FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
	//if (PropertyName == GET_MEMBER_NAME_CHECKED(UColoredMeshComponent, CurrentColor))
	//{
	//	//various uproperty tricks
	//	UNumericProperty* EnumProperty = Cast<UNumericProperty>(e.Property);
	//	FString StringValue = EnumProperty->GetNumericPropertyValueToString(&CurrentColor);
	//	int32 IntValue = FCString::Atoi(*StringValue);
	//	EHyperColorEnum EnumValue = static_cast<EHyperColorEnum>(IntValue);
	//	UE_LOG(LogTemp, Warning, TEXT("Current Color Changed in Editor!"));
	//	SetMeshColorSettings(EnumValue);
	//	
	//}
	
}

//void UColoredMeshComponent::SetMeshColorSettings(EHyperColorEnum newColor) 
//{
//	AActor* actor = Cast<AActor>(GetOwner());
//	if (actor)
//	{
//		//is actor
//		UStaticMeshComponent* mesh = Cast<UStaticMeshComponent>(actor->GetRootComponent());
//		if (mesh)
//		{
//
//			switch (newColor)
//			{
//			case EHyperColorEnum::HC_Yellow:
//				mesh->SetCollisionProfileName(FName("YellowObject"));
//				mesh->bGenerateOverlapEvents = true;
//				RecreatePhysicsState();
//
//				mesh->SetMaterial(0, YellowMaterial);
//				MarkRenderStateDirty();
//				break;
//			case EHyperColorEnum::HC_Pink:
//				mesh->SetCollisionProfileName(FName("PinkObject"));
//				mesh->bGenerateOverlapEvents = true;
//				RecreatePhysicsState();
//
//				mesh->SetMaterial(0, PinkMaterial);
//				MarkRenderStateDirty();
//				break;
//			case EHyperColorEnum::HC_Blue:
//				mesh->SetCollisionProfileName(FName("BlueObject"));
//				mesh->bGenerateOverlapEvents = true;
//				RecreatePhysicsState();
//
//				mesh->SetMaterial(0, BlueMaterial);
//				MarkRenderStateDirty();
//				break;
//			default:
//				break;
//			}
//		}
//	}
//}

