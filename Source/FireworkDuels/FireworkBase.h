// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickableObject.h"
#include "Components/CapsuleComponent.h"
#include "WickComponent.h"
#include "NiagaraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "FireworkBase.generated.h"

UCLASS()
class FIREWORKDUELS_API AFireworkBase : public APickableObject
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime);
	
public:	
	// Sets default values for this actor's properties
	AFireworkBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWickComponent* WickComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* WickCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraComponent* WickEmitter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsBurning;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageRadius = 25.f;

	UPROPERTY(EditDefaultsOnly)
	bool IsDummyObject;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float WickBurningTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float PostWickTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MultiShotCount;

	UPROPERTY()
	float WickRemainingTime;

	UFUNCTION(BlueprintCallable)
	virtual void SetFire();

	UFUNCTION(BlueprintCallable)
	virtual void Explode();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ExplodeEffects();

	UFUNCTION(BlueprintImplementableEvent)
	void OnTick();
};
