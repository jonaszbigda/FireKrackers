// Fill out your copyright notice in the Description page of Project Settings.


#include "FireworkBase.h"

// Sets default values
AFireworkBase::AFireworkBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
	//StaticMesh = RootComponent;
	

	if (!IsDummyObject) {
		WickComponent = CreateDefaultSubobject<UWickComponent>(TEXT("WickComponent"));
		WickComponent->SetupAttachment(RootComponent);
		WickComponent->SetMobility(EComponentMobility::Movable);
		WickCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("WickCollision"));
		WickCollision->SetupAttachment(RootComponent);
		WickEmitter = CreateDefaultSubobject<UNiagaraComponent>(TEXT("WickEmitter"));
		WickEmitter->SetupAttachment(RootComponent);
		WickComponent->EmitterReference = WickEmitter;
	}
}

void AFireworkBase::BeginPlay()
{
	Super::BeginPlay();
}

void AFireworkBase::Tick(float DeltaTime)
{
	OnTick();
	if (IsBurning)
	{
		WickRemainingTime -= DeltaTime;
		WickComponent->UpdateWickBurnEffects((WickBurningTime - WickRemainingTime) / WickBurningTime);

		if (WickRemainingTime <= 0.f)
		{
			Explode();
		}
	}
}

void AFireworkBase::SetFire()
{
	WickRemainingTime = WickBurningTime;
	if (IsValid(WickEmitter)) {
		WickEmitter->Activate(true);
	}
	IsBurning = true;
}

void AFireworkBase::Explode()
{
	IsBurning = false;
	ExplodeEffects();
}