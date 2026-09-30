// All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingBlock.h"
#include "Math/UnrealMathUtility.h"
#include "LevelTemplate.h"
#include "SpawnManager.generated.h"

UCLASS()
class FIREWORKDUELS_API ASpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnManager();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Distance = 45.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 BlocksX = 10;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 BlocksY = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MaxVariants = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ALevelTemplate* CurrentLevel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<int32, TSubclassOf<ABuildingBlock>> BlockTemplates;

	UPROPERTY(BlueprintReadWrite)
	int32 SpawnedBlocks = 0;

	UFUNCTION(BlueprintCallable, CallInEditor)
	void GenerateBoard(const TSubclassOf<ALevelTemplate> Template);

	UFUNCTION()
	void RemoveBlock();

	UFUNCTION(BlueprintImplementableEvent)
	void OnLevelCompleted(const float &Playtime,const int32 &AcquiredStars);

public:	

};
