// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawnBase.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "Snake_C.h"
#include "Components/InputComponent.h"

// Sets default values
APlayerPawnBase::APlayerPawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCamera"));
	RootComponent = PawnCamera;
}

void APlayerPawnBase::HandlePlayerVerticalInput(float value)
{
	if (IsValid(SnakeActor))
	{
		if (value > 0 && SnakeActor->LastMoveDirection != EMovementDirection::DOWN)
		{
			if (SnakeActor->Waiting == false)
			{
				SnakeActor->LastMoveDirection = EMovementDirection::UP;
				SnakeActor->Waiting = true;
			}
		}
		else if (value < 0 && SnakeActor->LastMoveDirection != EMovementDirection::UP)
		{
			if (SnakeActor->Waiting == false)
			{
				SnakeActor->LastMoveDirection = EMovementDirection::DOWN;
				SnakeActor->Waiting = true;
			}
		}
	}
}

void APlayerPawnBase::HandlePlayerHorizontalInput(float value)
{
	if (IsValid(SnakeActor))
	{
		if (value > 0 && SnakeActor->LastMoveDirection != EMovementDirection::LEFT)
		{
			if (SnakeActor->Waiting == false)
			{
				SnakeActor->LastMoveDirection = EMovementDirection::RIGHT;
				SnakeActor->Waiting = true;
			}
		}
		else if (value < 0 && SnakeActor->LastMoveDirection != EMovementDirection::RIGHT)
		{
			if (SnakeActor->Waiting == false)
			{
				SnakeActor->LastMoveDirection = EMovementDirection::LEFT;
				SnakeActor->Waiting = true;
			}
		}
	}
}

// Called when the game starts or when spawned
void APlayerPawnBase::BeginPlay()
{
	Super::BeginPlay();

	SetActorRotation(FRotator(-90.f, 0.f, 0.f));
	CreateSnakeActor();
	SetActorTickInterval(SnakeActor->MovementSpeed + 0.05);
}

// Called every frame
void APlayerPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Vertical", this, &APlayerPawnBase::HandlePlayerVerticalInput);
	PlayerInputComponent->BindAxis("Horizontal", this,&APlayerPawnBase::HandlePlayerHorizontalInput);

}

void APlayerPawnBase::CreateSnakeActor()
{
	SnakeActor = GetWorld()->SpawnActor<ASnake_C>(SnakeActorClass, FTransform());
}
