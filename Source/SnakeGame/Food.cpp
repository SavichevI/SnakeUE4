// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "PlayingFieldBace.h"
#include "Snake_C.h"
#include "BlockBace.h"
#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>

// Sets default values
AFood::AFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshFood = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshFood"));
	RootComponent = MeshFood;
}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();
	
	ScaleFood = MeshFood->GetRelativeScale3D();
	bLimit = true;

}

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (ScaleFood != FVector(0.5, 0.5, 0.5) && bLimit == true)
	{
		ScaleFood = ScaleFood - FVector(0.005, 0.005, 0.005);
		MeshFood->SetRelativeScale3D(ScaleFood);
		
		if (ScaleFood.X <= 0.5 && ScaleFood.Y <= 0.5 && ScaleFood.Z <= 0.5)
		{
			bLimit = false;
			
		}
	}
	else if (ScaleFood != FVector(1.f, 1.f, 1.f) && bLimit == false)
	{
		ScaleFood = ScaleFood + FVector(0.005, 0.005, 0.005);
		MeshFood->SetRelativeScale3D(ScaleFood);
		if (ScaleFood.X >= 1 && ScaleFood.Y >= 1 && ScaleFood.Z >= 1)
		{
			bLimit = true;
		}
	}
	
}

void AFood::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		auto Block = Cast<ABlockBace>(Interactor);
		Snake = Cast<ASnake_C>(Interactor);
		
		if (IsValid(Snake))
		{
			Snake->AddSnakeElements();
			DestroyFood = true;
			//PlayingField.GetDefaultObject()->CreateNewFood();
			this->Destroy();
			
		}
		
	}
}

