// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeElementBace.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Snake_C.h"
#include "BlockBace.h"

// Sets default values
ASnakeElementBace::ASnakeElementBace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyComponent"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void ASnakeElementBace::SetFirstElementType_Implementation()
{
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ASnakeElementBace::HandleBeginOverlap);
}

void ASnakeElementBace::HandleBeginOverlap(UPrimitiveComponent* OverlappedCommponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OfherComp, 
	int32 OfherBadyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if (IsValid(SnakeOwner))
	{
		SnakeOwner->SnakeElementOveplap(this, OtherActor);
	}
}

void ASnakeElementBace::ToggleCollision()
{
	if (MeshComponent->GetCollisionEnabled() == ECollisionEnabled::NoCollision)
	{
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

// Called when the game starts or when spawned
void ASnakeElementBace::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASnakeElementBace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASnakeElementBace::Interact(AActor* Interactor, bool bIsHead)
{
	auto Snake = Cast<ASnake_C>(Interactor);
	if (IsValid(Snake))
	{
		Snake->Destroy();
	}
}

