// All rights reserved.


#include "SpawnManager.h"

// Sets default values
ASpawnManager::ASpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ASpawnManager::GenerateBoard(const TSubclassOf<ALevelTemplate> Template) {
	SpawnedBlocks = 0;
	FVector ActorLocation = this->GetActorLocation();
	CurrentLevel = GetWorld()->SpawnActor<ALevelTemplate>(Template, this->GetActorTransform());
	UPaperTileMapComponent* Tilemap = CurrentLevel->Template;

	TArray<TSubclassOf<ABuildingBlock>> Classes;

	for (int32 i = 0; i < BlocksY; i++) {
		for (int32 o = 0; o < BlocksX; o++) {
			int32 TileId = Tilemap->GetTile(i, o, 0).GetTileIndex();

			// If TileId == 4 means, that there should be no tile at this location
			if (TileId != 4) {
				// Make transform
				FTransform SpawnTransform;
				SpawnTransform.SetLocation(FVector((ActorLocation.X - (Distance * BlocksX / 2) + (o * Distance)), (ActorLocation.Y - (Distance * (BlocksY / 2)) + (i * Distance)), ActorLocation.Z));

				// Spawn block
				TSubclassOf<ABuildingBlock> TileClass = *BlockTemplates.Find(TileId);
				ABuildingBlock* ThisBlock = GetWorld()->SpawnActor<ABuildingBlock>(TileClass, SpawnTransform);
				ThisBlock->Index = (10 * i) + o;
				if (ThisBlock->HasVariants) {
					ThisBlock->Variant = FMath::RandRange(1, MaxVariants);
				}
				if (TileId != 5) {
					SpawnedBlocks++;
					ThisBlock->OnBlockDestroyed.BindUFunction(this, TEXT("RemoveBlock"));
				}
				ThisBlock->FadeIn();
			}
		}
	}
}

void ASpawnManager::RemoveBlock() {
	SpawnedBlocks--;
	UE_LOG(LogTemp, Warning, TEXT("Removed Block --- %i left"), SpawnedBlocks);
	if (SpawnedBlocks <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("All blocks destroyed, calling OnLevelCompleted"));
		float Playtime = CurrentLevel->StopGame();
		int32 AcquiredStars = CurrentLevel->GetAwardStars();

		OnLevelCompleted(Playtime, AcquiredStars);
	}
}