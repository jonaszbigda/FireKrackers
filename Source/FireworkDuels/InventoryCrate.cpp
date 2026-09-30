// All rights reserved.


#include "InventoryCrate.h"

// Sets default values
AInventoryCrate::AInventoryCrate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	ItemMesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh1"));
	ItemMesh1->SetupAttachment(StaticMesh);
	ItemMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh2"));
	ItemMesh2->SetupAttachment(StaticMesh);
}

// Called when the game starts or when spawned
void AInventoryCrate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInventoryCrate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FloatItemMeshes(DeltaTime);
}

void AInventoryCrate::FloatItemMeshes(float DeltaTime)
{
	if (Show1)
	{
		ItemMesh1->AddRelativeRotation(FRotator(0.f, 0.f, (30.f * DeltaTime)));
	}

	if (Show2)
	{
		ItemMesh2->AddRelativeRotation(FRotator(0.f, 0.f, (30.f * DeltaTime)));
	}
}