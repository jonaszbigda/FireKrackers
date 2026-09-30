// Fill out your copyright notice in the Description page of Project Settings.

#include "WristMenuActor.h"

// Sets default values
AWristMenuActor::AWristMenuActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	Spline->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWristMenuActor::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AWristMenuActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Invoke inventory menu
void AWristMenuActor::InvokeInventoryMenu()
{

}

void AWristMenuActor::RevokeInventoryMenu()
{

}

void AWristMenuActor::UpdateInventory(FInventory NewInventory) {

}