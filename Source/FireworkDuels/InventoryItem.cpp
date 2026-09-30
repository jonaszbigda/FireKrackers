// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItem.h"

// Sets default values
AInventoryItem::AInventoryItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	RootComponent = StaticMeshComponent;
	StaticMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetupAttachment(RootComponent);
	Collision->SetSphereRadius(CollisionRadius);
	Collision->SetCollisionObjectType(ECollisionChannel::ECC_Vehicle);
	Collision->SetCollisionProfileName(TEXT("OverpalAll"));
}

// Called when the game starts or when spawned
void AInventoryItem::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AInventoryItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Initailize
void AInventoryItem::Initialize()
{
	StaticMeshComponent->SetStaticMesh(StaticMesh);

}