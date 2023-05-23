// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "SpeedBonusBace.generated.h"

class UStaticMeshComponent;

UCLASS()
class SNAKEGAME_API ASpeedBonusBace : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpeedBonusBace();	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact(AActor* Interactor, bool bIsHead) override;
	UPROPERTY()
		bool bDestroySpeedBonus;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		UStaticMeshComponent* SpeedBonusMesh;
};
