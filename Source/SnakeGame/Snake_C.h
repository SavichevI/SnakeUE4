// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Snake_C.generated.h"


class ASnakeElementBace;
class APlayingFieldBace;
class ASpeedBonusBace;

UENUM()
enum class EMovementDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

UCLASS()
class SNAKEGAME_API ASnake_C : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnake_C();
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASnakeElementBace> SnakeElementClass;

	UPROPERTY()
	TArray<ASnakeElementBace*> SnakeElements;

	UPROPERTY(EditDefaultsOnly)
	float ElementSize;

	UPROPERTY()
	EMovementDirection LastMoveDirection;

	UPROPERTY(EditDefaultsOnly)
	float MovementSpeed;

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ASpeedBonusBace* SpeedBonus;*/

	UPROPERTY()
	float Temporary;

	UPROPERTY()
	FTimerHandle Timer;

	UPROPERTY(EditDefaultsOnly)
	float TimerTime;

	UPROPERTY()
	bool Waiting;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void AddSnakeElements(int ElementNum = 1);
	UFUNCTION()
	void Move();
	UFUNCTION()
	void SnakeElementOveplap(ASnakeElementBace* OverlappedElement, AActor* Other);
	UFUNCTION()
	void PlusSpeed();
	UFUNCTION()
	void BackSpeed();

};
