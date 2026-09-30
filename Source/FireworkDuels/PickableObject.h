// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Animation/AnimSequenceBase.h"
#include "PickableObject.generated.h"

UCLASS()
class FIREWORKDUELS_API APickableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickableObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMesh* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool CanBeGrabbed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimSequenceBase* GrabAnimMod;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FTransform InventoryAdditionalTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsHeld;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EControllerHand ThrowingHand;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool IsRocket = false;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnUsed();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnEndUsed();

	UFUNCTION(BlueprintImplementableEvent)
	void ThrowEffects();
};
