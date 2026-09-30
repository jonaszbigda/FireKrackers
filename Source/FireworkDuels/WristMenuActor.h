// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomDataTypes.h"
#include "PickableObject.h"
#include "InventoryItem.h"
#include "FireworksPawn.h"
#include "Components/SplineComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SceneComponent.h"
#include "WristMenuActor.generated.h"

UCLASS()
class FIREWORKDUELS_API AWristMenuActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWristMenuActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Variables

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USplineComponent* Spline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInventory Inventory;

	// Methods

	UFUNCTION(BlueprintCallable)
	void InvokeInventoryMenu();

	UFUNCTION(BlueprintCallable)
	void RevokeInventoryMenu();

	UFUNCTION(BlueprintCallable)
	void UpdateInventory(FInventory NewInventory);

};
