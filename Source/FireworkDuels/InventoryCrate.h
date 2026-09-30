// All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "CustomDataTypes.h"
#include "FireworkBase.h"
#include "InventoryCrate.generated.h"

UCLASS()
class FIREWORKDUELS_API AInventoryCrate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInventoryCrate();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ItemMesh1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ItemMesh2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool Show1 = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool Show2 = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<Firework> Item1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<Firework> Item2;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void FloatItemMeshes(float DeltaTime);

};
