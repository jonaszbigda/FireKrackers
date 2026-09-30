// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "WickComponent.generated.h"


UCLASS()
class FIREWORKDUELS_API UWickComponent : public USplineMeshComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UPROPERTY()
	UNiagaraComponent* EmitterReference;

	UPROPERTY()
	UMaterialInstanceDynamic* DynamicMaterialReference;

	// This function calculates new position of where the wick is currently burning.
	UFUNCTION(BlueprintCallable)
	FTransform UpdateWickBurnEffects(float Alpha);
};
