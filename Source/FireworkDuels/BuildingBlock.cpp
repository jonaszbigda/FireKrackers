// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingBlock.h"

// Sets default values
ABuildingBlock::ABuildingBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
}

void ABuildingBlock::TakeHit() {
	HitsRemaining -= 1;

	if (HitsRemaining <= 0) {
		Ripple();
		DestroyBlock();
	}
}

TArray<ABuildingBlock*> ABuildingBlock::GetSameVariantNeighbours() {
	TArray<ABuildingBlock*> Results;
	FVector Location = this->GetActorLocation();
	
	for (int32 i = 0; i < 4; i++) {
		FHitResult HitResult;
		FVector EndLocation;

		switch (i) {
		case 0:
			EndLocation = Location + FVector(60.f, 0.f, 0.f);
			break;
		case 1:
			EndLocation = Location + FVector(-60.f, 0.f, 0.f);
			break;
		case 2:
			EndLocation = Location + FVector(0.f, 60.f, 0.f);
			break;
		case 3:
			EndLocation = Location + FVector(0.f, -60.f, 0.f);
			break;
		}

		if (GetWorld()->LineTraceSingleByChannel(HitResult, Location, EndLocation, ECC_Visibility)) {
			ABuildingBlock* HitActor = Cast<ABuildingBlock>(HitResult.GetActor());
			if (IsValid(HitActor) && HitActor->Variant == this->Variant) {
				Results.Add(HitActor);
			}
		}
	}

	return Results;
}

void ABuildingBlock::DestroyBlock_Implementation() {
	if (!IsBeingDestroyed) {
		IsBeingDestroyed = true;
		OnBlockDestroyed.ExecuteIfBound();
	}
}

void ABuildingBlock::DestroyWithDelay_Implementation() {
	if (!IsBeingDestroyed) {
		IsBeingDestroyed = true;
		OnBlockDestroyed.ExecuteIfBound();
	}
}

void ABuildingBlock::Ripple() {

	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;
	TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Visibility));

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);

	TArray<AActor*> OutActors;

	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), this->GetActorLocation(), RippleRadius, TraceObjectTypes, ABuildingBlock::StaticClass(), IgnoreActors, OutActors);

	for (AActor* OverlappedActor : OutActors) {
		ABuildingBlock* ThisBlock = Cast<ABuildingBlock>(OverlappedActor);
		if (ThisBlock && !ThisBlock->IsBeingDestroyed) {
			float ThisDistance = UKismetMathLibrary::Vector_Distance(this->GetActorLocation(), ThisBlock->GetActorLocation());
			ThisBlock->RippleEffects(ThisDistance);
		}
	}
}