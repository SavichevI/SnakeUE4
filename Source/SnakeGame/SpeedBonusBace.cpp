// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedBonusBace.h"
#include "Snake_C.h"

// Sets default values
ASpeedBonusBace::ASpeedBonusBace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpeedBonusMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpeedBonusMesh"));
	RootComponent = SpeedBonusMesh;
}

// Called when the game starts or when spawned
void ASpeedBonusBace::BeginPlay()
{
	Super::BeginPlay();

}

void ASpeedBonusBace::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		auto Snake = Cast<ASnake_C>(Interactor);
		if (IsValid(Snake))
		{
			Snake->AddSnakeElements();
			//bDestroySpeedBonus = true;
			Snake->PlusSpeed();
			this->Destroy();
			
		}
	}
}

// Called every frame
void ASpeedBonusBace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

