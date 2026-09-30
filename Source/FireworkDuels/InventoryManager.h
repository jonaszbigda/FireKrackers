// All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomDataTypes.h"
#include "GameFramework/Pawn.h"
#include "InventoryManager.generated.h"

UCLASS()
class FIREWORKDUELS_API AInventoryManager : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	TMap<APawn*, FInventory> Inventory;
};