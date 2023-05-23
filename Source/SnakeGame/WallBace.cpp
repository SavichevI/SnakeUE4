// Fill out your copyright notice in the Description page of Project Settings.


#include "WallBace.h"
#include "Snake_C.h"

// Sets default values
AWallBace::AWallBace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall"));
	RootComponent = WallMesh;
}

// Called when the game starts or when spawned
void AWallBace::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWallBace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWallBace::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		auto SnakeActor = Cast<ASnake_C>(Interactor);
		if(IsValid(SnakeActor))
		{
			SnakeActor->Destroy();
		}
	}
}

