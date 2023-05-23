// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayingFieldBace.h"
#include "Engine/TriggerBox.h"
#include "Food.h"
#include "SpeedBonusBace.h"
#include "Snake_C.h"
#include "BlockBace.h"
#include "PlayerPawnBase.h"
#include "SnakeElementBace.h"
#include "Engine/Classes/Components/BoxComponent.h"
#include "Engine/Classes/Kismet/KismetMathLibrary.h"

// Sets default values
APlayingFieldBace::APlayingFieldBace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	ForBonus = -1;
	HowDeforeBonus = 5;
	HowManyBlock = 5;
}

void APlayingFieldBace::CreateNewFood()
{
	AFood* FoodActor = GetWorld()->SpawnActor<AFood>(FoodMesh, UKismetMathLibrary::RandomPointInBoundingBox(BoxLocation, BoxScaleExtent), FRotator(1, 1, 1));

	for (int i = 0; i < HowManyBlock; i++)
	{
		BoxScaleExtent = Box->GetScaledBoxExtent();
		BoxLocation = Box->GetRelativeLocation();
		auto Random = UKismetMathLibrary::RandomPointInBoundingBox(FVector(BoxLocation.X, BoxLocation.Y, 0) , BoxScaleExtent);
		ABlockBace* BlockElements = GetWorld()->SpawnActor<ABlockBace>(BlockMesh, Random, FRotator(1, 1, 1));

		if (IsValid(Snake))
		{
			for(int y = Snake->SnakeElements.Num() - 1; y > 0; y--)
			{
				auto PrevElement = Snake->SnakeElements[y];
			
				if (BlockElements->GetActorLocation() == PrevElement->GetActorLocation())
				{
					BlockElements->SetActorLocation(FVector(0, 0, -500));
				}
			}

		}
		ArrayOfBlock.Add(BlockElements);
	}
	ForBonus++;
}

void APlayingFieldBace::CreateBonus()
{
	GetWorld()->SpawnActor<ASpeedBonusBace>(BonusMesh, UKismetMathLibrary::RandomPointInBoundingBox(BoxLocation, BoxScaleExtent), FRotator(1, 1, 1));
	ForBonus = 0;
}

void APlayingFieldBace::DestroyBlock()
{
	for (int i = ArrayOfBlock.Num() - 1; i > 0; i--)
	{
		ArrayOfBlock[i]->DestroyBlock();
		ArrayOfBlock.Pop();
	}
}

// Called when the game starts or when spawned
void APlayingFieldBace::BeginPlay()
{
	Super::BeginPlay();
	CreateNewFood();
	BoxScaleExtent = Box->GetScaledBoxExtent();
	BoxLocation = Box->GetRelativeLocation();
}

// Called every frame
void APlayingFieldBace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ForBonus==HowDeforeBonus)
	{
		CreateBonus();
		ForBonus = 0;
	}

}

void APlayingFieldBace::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		Snake = Cast<ASnake_C>(Interactor);	
	}
}
