// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "PlayingFieldBace.generated.h"

class UBoxComponent;
class AFood;
class ASpeedBonusBace;
class ASnake_C;
class ABlockBace;
class APlayerPawnBase;
class ASnakeElementBace;

UCLASS()
class SNAKEGAME_API APlayingFieldBace : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayingFieldBace();
	UFUNCTION(BlueprintCallable)
		virtual void CreateNewFood();
	UFUNCTION(BlueprintCallable)
		virtual void CreateBonus();
	UFUNCTION(BlueprintCallable)
		void DestroyBlock();
	//UFUNCTION()


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact(AActor* Interactor, bool bIsHead) override;
	UPROPERTY(BlueprintReadOnly)
		UBoxComponent* Box;

	//UPROPERTY(EditDefaultsOnly)
	//	UStaticMeshComponent* Wall;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AFood> FoodMesh;

	UPROPERTY()
		FVector BoxScaleExtent;

	UPROPERTY()
		FVector BoxLocation;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ASpeedBonusBace> BonusMesh;

	UPROPERTY()
		ASnake_C* Snake;

	UPROPERTY(BlueprintReadWrite)
		int32 ForBonus;

	UPROPERTY(EditDefaultsOnly)
		int32 HowDeforeBonus;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ABlockBace> BlockMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		int32 HowManyBlock;
	
	UPROPERTY()
		TArray<ABlockBace*> ArrayOfBlock;
	
	UPROPERTY()
		FVector SnakeLocation;

};
