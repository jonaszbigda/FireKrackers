// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FireworkBase.h"
#include "BuildingBlock.h"
#include "LevelTemplate.h"
#include "Engine/Texture.h"
#include "Engine/World.h"
#include "Engine/DataTable.h"
#include "UObject/SoftObjectPtr.h"
#include "CustomDataTypes.generated.h"

UENUM(BlueprintType)
enum FireworksCategory
{
	Firecracker UMETA(DisplayName="Firecracker"),
	RomanFire UMETA(DisplayName = "RomanFire"),
	Rocket UMETA(DisplayName = "Rocket"),
	None UMETA(DisplayName="None")
};

UENUM(BlueprintType)
enum Firework
{
	Impact UMETA(DisplayName = "Impact"),
	Sticky UMETA(DisplayName = "Sticky"),
	Cluster UMETA(DisplayName = "Cluster"),
	ImpactRocket UMETA(DisplayName = "ImpactRocket"),
	ClusterRocket UMETA(DisplayName = "ClusterRocket"),
	GuidedRocket UMETA(DisplayName = "GuidedRocket"),

	Lighter UMETA(DisplayName = "Lighter"),
};

// LevelData
USTRUCT(BlueprintType)
struct FIREWORKDUELS_API FLevelData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftClassPtr<ALevelTemplate> LevelTemplateClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OneStarTime = 120.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TwoStarTime = 90.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ThreeStarTime = 75.f;

};

// LevelSaveData
USTRUCT(BlueprintType)
struct FIREWORKDUELS_API FLevelSaveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsUnlocked = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ObtainedStars = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BestTime = 999.f;
};

// Firework data
USTRUCT(BlueprintType)
struct FIREWORKDUELS_API FFireworkData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<Firework> Firework;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<FireworksCategory> Category;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Price;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AFireworkBase> Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon = nullptr;
};


// Inventory
USTRUCT(BlueprintType)
struct FIREWORKDUELS_API FInventory
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FFireworkData> Items;
};