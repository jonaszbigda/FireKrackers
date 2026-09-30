// All rights reserved.


#include "LevelTemplate.h"

// Sets default values
ALevelTemplate::ALevelTemplate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Template = CreateDefaultSubobject<UPaperTileMapComponent>(TEXT("TemplateTilemap"));
	Template->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALevelTemplate::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALevelTemplate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CountTime) {
		GameTime += DeltaTime;
	}
}

void ALevelTemplate::StartGame() {
	CountTime = true;
	GameTime = 0.f;
}

float ALevelTemplate::StopGame() {
	CountTime = false;
	return GameTime;
}

int32 ALevelTemplate::GetAwardStars() {
	if (GameTime <= ThreeStarTarget)
	{
		return 3;
	}
	else if (GameTime <= TwoStarTarget) 
	{
		return 2;
	}
	else if (GameTime <= OneStarTarget)
	{
		return 1;
	}
	else {
		return 0;
	}
}