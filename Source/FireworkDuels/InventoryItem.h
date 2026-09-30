// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CustomDataTypes.h"
#include "GameFramework/Actor.h"
#include "InventoryItem.generated.h"

UCLASS()
class FIREWORKDUELS_API AInventoryItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInventoryItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* Collision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* StaticMesh;

	UPROPERTY(BlueprintReadOnly)
	FFireworkData FireworkData;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float TargetDistanceAlongSpline;

	UPROPERTY(EditAnywhere)
	bool bIsFirework;

	UPROPERTY(EditDefaultsOnly)
	float CollisionRadius;

	UFUNCTION()
	void Initialize();

	UFUNCTION(BlueprintImplementableEvent)
	void TryDestroy();

};
