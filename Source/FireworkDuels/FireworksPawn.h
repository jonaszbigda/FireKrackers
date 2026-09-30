// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SceneComponent.h"
#include "PickableObject.h"
#include "MotionControllerComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "WickComponent.h"
#include "Components/WidgetInteractionComponent.h"
#include "DrawDebugHelpers.h"
#include "CustomDataTypes.h"
#include "FireworksPawn.generated.h"

UCLASS()
class FIREWORKDUELS_API AFireworksPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFireworksPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Components

	UPROPERTY(VisibleAnywhere)
	USceneComponent* PawnRoot;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* CameraRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* VRCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UMotionControllerComponent* MotionControllerR;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UMotionControllerComponent* MotionControllerL;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* LeftHandMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* RightHandMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* RightHandCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* LeftHandCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* LaserL;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* LaserR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetInteractionComponent* WidgetInteractionL;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetInteractionComponent* WidgetInteractionR;

	// Variables

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FFireworkData> Inventory;

	UPROPERTY(BlueprintReadWrite)
	APickableObject* HeldObject_R;

	UPROPERTY(BlueprintReadWrite)
	APickableObject* HeldObject_L;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Cash;

	UPROPERTY(BlueprintReadWrite)
	APickableObject* HoveredActorR;

	UPROPERTY(BlueprintReadWrite)
	APickableObject* HoveredActorL;

	UPROPERTY(BlueprintReadWrite)
	bool IsGrabbingR;

	UPROPERTY(BlueprintReadWrite)
	bool IsGrabbingL;

	UPROPERTY(BlueprintReadWrite)
	bool TryShowLaserR;

	UPROPERTY(BlueprintReadWrite)
	bool TryShowLaserL;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool DrawApproximationDebug = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throwing")
	float ThrowVelocityMultiplier = 1.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FHitResult CurrentLaserHitL;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FHitResult CurrentLaserHitR;

	// How much velocity samples should be recorded for throwing direction approximation
	UPROPERTY(EditDefaultsOnly, Category = "Throwing")
	int32 VelocitySamples = 5;

	TArray<FVector> VelocitySamples_L;
	TArray<FVector> VelocitySamples_R;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EControllerHand DominatingHand = EControllerHand::Right;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool IsSteamVR = false;

	// Functions

	// Try to grab object
	UFUNCTION(BlueprintCallable)
	bool TryGrab(EControllerHand Hand);

	// Drop object
	UFUNCTION(BlueprintCallable)
	bool Drop(EControllerHand Hand);

	// Attach grabbed object to the hand at specified socket transform
	UFUNCTION(BlueprintCallable)
	void SetupGrabAttachment(EControllerHand Hand);

	// Throw an object
	void ThrowObject(APickableObject* Object, EControllerHand Hand);

	// Sample hand velocities
	void SampleHandVelocities();

	// Approximate throw velocity
	FVector ApproximateThrowVelocity(EControllerHand Hand);

	// ABA ABA
	UFUNCTION(BlueprintCallable)
	void EnableLaserOnHand(EControllerHand Hand);

	UFUNCTION(BlueprintCallable)
	void DisableLaserOnHand(EControllerHand Hand);

	UFUNCTION()
	void TryUpdateLasers();
};
