// Fill out your copyright notice in the Description page of Project Settings.


#include "Snake_C.h"
#include "SnakeElementBace.h"
#include "Interactable.h"
#include "PlayingFieldBace.h"
#include "SpeedBonusBace.h"
//#include "Math/UnrealMathUtility.h"

// Sets default values
ASnake_C::ASnake_C()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 100.f;
	MovementSpeed = 0,5;
	LastMoveDirection = EMovementDirection::LEFT;
	TimerTime = 5;
}

// Called when the game starts or when spawned
void ASnake_C::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(MovementSpeed);
	AddSnakeElements(4);
	Temporary = MovementSpeed;
}

// Called every frame
void ASnake_C::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();

}

void ASnake_C::AddSnakeElements(int ElementNum)
{
	for (int i = 0; i < ElementNum; i++)
	{
		FVector NewLocation = FVector(SnakeElements.Num() * ElementSize,0,50);
		FTransform NewTransform(NewLocation);	
		ASnakeElementBace* SnakeElem = GetWorld()->SpawnActor<ASnakeElementBace>(SnakeElementClass, NewTransform);
		SnakeElem->SnakeOwner = this;
		int32 ElemIndex = SnakeElements.Add(SnakeElem);
		if (ElemIndex == 0)
		{
			SnakeElem->SetFirstElementType();
		}
	}
	
}

void ASnake_C::Move()
{
	FVector MovementVector(ForceInitToZero);
	switch (LastMoveDirection)
	{
	case EMovementDirection::UP:
		MovementVector.X += ElementSize;
		Waiting = false;
		break;
	case EMovementDirection::DOWN:
		MovementVector.X -= ElementSize;
		Waiting = false;
		break;
	case EMovementDirection::LEFT:
		MovementVector.Y += ElementSize;
		Waiting = false;
		break;
	case EMovementDirection::RIGHT:
		MovementVector.Y -= ElementSize;
		Waiting = false;
		break;
	default:
		break;
	}

	SnakeElements[0]->ToggleCollision();

	for (int i = SnakeElements.Num() - 1; i > 0; i--)
	{
		auto CurretElement = SnakeElements[i];
		auto PrevEltment = SnakeElements[i - 1];
		FVector PrevLocation = PrevEltment->GetActorLocation();
		CurretElement->SetActorLocation(PrevLocation);
	}

	SnakeElements[0]->AddActorWorldOffset(MovementVector);
	SnakeElements[0]->ToggleCollision(); 

}

void ASnake_C::SnakeElementOveplap(ASnakeElementBace* OverlappedElement, AActor* Other)
{
	if (IsValid(OverlappedElement))
	{
		int32 ElementIndex;
		SnakeElements.Find(OverlappedElement, ElementIndex);
		bool bIsFirst = ElementIndex == 0;
		IInteractable* InteractableInterface = Cast<IInteractable>(Other);
		if (InteractableInterface)
		{
			InteractableInterface->Interact(this, bIsFirst);
			
		}
		
	}
}

void ASnake_C::PlusSpeed()
{
	if (FMath::RandRange(0, 1) == 0)
	{
		MovementSpeed = Temporary / 3;
		SetActorTickInterval(MovementSpeed);
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &ASnake_C::BackSpeed, TimerTime, false);
	}
	else
	{
		MovementSpeed = Temporary * 3;
		SetActorTickInterval(MovementSpeed);
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &ASnake_C::BackSpeed, TimerTime, false);
	}
	
}

void ASnake_C::BackSpeed()
{
	MovementSpeed = Temporary;
	SetActorTickInterval(MovementSpeed);
}

