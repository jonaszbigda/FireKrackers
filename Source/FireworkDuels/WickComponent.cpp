// Fill out your copyright notice in the Description page of Project Settings.


#include "WickComponent.h"

// Called when the game starts
void UWickComponent::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(GetStaticMesh().Get()))
	{
		DynamicMaterialReference = UMaterialInstanceDynamic::Create(GetStaticMesh().Get()->GetMaterial(0), this);
		SetMaterial(0, DynamicMaterialReference);
	}
}


FTransform UWickComponent::UpdateWickBurnEffects(float Alpha)
{
	FTransform CurrentTransform = CalcSliceTransformAtSplineOffset(1.f - Alpha);

	if (IsValid(EmitterReference))
	{
		EmitterReference->SetWorldLocation(UKismetMathLibrary::TransformLocation(GetComponentTransform(), CurrentTransform.GetLocation()));
	}

	if (IsValid(DynamicMaterialReference))
	{
		DynamicMaterialReference->SetScalarParameterValue(TEXT("Alpha"), Alpha);
		DynamicMaterialReference->SetVectorParameterValue(TEXT("BurnLocation"), UKismetMathLibrary::TransformLocation(GetComponentTransform(), CurrentTransform.GetLocation()));
	}

	return CurrentTransform;
}