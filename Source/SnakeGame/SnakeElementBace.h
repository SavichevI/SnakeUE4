// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "SnakeElementBace.generated.h"

class UStaticMeshComponent;
class ASnake_C;

UCLASS()
class SNAKEGAME_API ASnakeElementBace : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnakeElementBace();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComponent;
	UFUNCTION(BlueprintNativeEvent)
	void SetFirstElementType();
	void SetFirstElementType_Implementation();
	UFUNCTION()
	void HandleBeginOverlap(UPrimitiveComponent* OverlappedCommponent,
			AActor* OtherActor,
			UPrimitiveComponent* OfherComp,
			int32 OfherBadyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);
	UPROPERTY()
	ASnake_C* SnakeOwner;
	UFUNCTION()
	void ToggleCollision();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact(AActor* Interactor, bool bIsHead) override;

};
