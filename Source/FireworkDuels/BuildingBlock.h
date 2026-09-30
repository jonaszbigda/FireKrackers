// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h" 
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "BuildingBlock.generated.h"

DECLARE_DELEGATE(FBlockDestroyed);

UCLASS()
class FIREWORKDUELS_API ABuildingBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildingBlock();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;

	// How many hits can this block take before getting destroyed
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 HitsRemaining = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool CanChain = false;

	UPROPERTY(BlueprintReadOnly)
	int32 Index = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool HasVariants = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Variant = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float RippleRadius = 200.f;

	UPROPERTY(BlueprintReadOnly)
	bool IsBeingDestroyed = false;

	FBlockDestroyed OnBlockDestroyed;

	UFUNCTION(BlueprintCallable)
	void TakeHit();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DestroyBlock();

	UFUNCTION(BlueprintImplementableEvent)
	void FadeIn();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DestroyWithDelay();

	UFUNCTION()
	void Ripple();

	UFUNCTION(BlueprintImplementableEvent)
	void RippleEffects(float Distance);

	// Get neighbouring Blocks with same color variant
	UFUNCTION(BlueprintCallable)
	TArray<ABuildingBlock*> GetSameVariantNeighbours();

};
