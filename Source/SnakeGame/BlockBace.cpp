// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockBace.h"
#include "PlayingFieldBace.h"
#include "Snake_C.h"
#include "Engine/Classes/Kismet/KismetMathLibrary.h"

// Sets default values
ABlockBace::ABlockBace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh"));
	RootComponent = BlockMesh;
}

void ABlockBace::DestroyBlock()
{
	this->Destroy();
}

void ABlockBace::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		auto Snake = Cast<ASnake_C>(Interactor);
		if (IsValid(Snake))
		{
			Snake->Destroy();
		}
	}
	
}

// Called when the game starts or when spawned
void ABlockBace::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlockBace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


