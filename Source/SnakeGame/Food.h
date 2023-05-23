// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Food.generated.h"

class APlayingFieldBace;
class ASnake_C;

UCLASS()
class SNAKEGAME_API AFood : public AActor, public IInteractable
{
	GENERATED_BODY()
	
private:
	FVector ScaleFood;
	bool bLimit;


public:	
	// Sets default values for this actor's properties
	AFood();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact(AActor* Interactor, bool bIsHead) override;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UStaticMeshComponent* MeshFood;

	UPROPERTY(EditDefaultsOnly)
	bool DestroyFood;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<APlayingFieldBace> PlayingField;

	UPROPERTY()
		ASnake_C* Snake;


};
