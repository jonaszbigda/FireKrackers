// All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperTileMapComponent.h"
#include "Components/SceneComponent.h"
#include "LevelTemplate.generated.h"

UCLASS()
class FIREWORKDUELS_API ALevelTemplate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelTemplate();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UPaperTileMapComponent* Template;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float OneStarTarget = 180.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TwoStarTarget = 120.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float ThreeStarTarget = 60.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float GameTime = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CountTime = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 LevelIndex = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void StartGame();

	// Stop counting and return elapsed game time
	UFUNCTION(BlueprintCallable)
	float StopGame();

	UFUNCTION(BlueprintCallable)
	int32 GetAwardStars();
};
