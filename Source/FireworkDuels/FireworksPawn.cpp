// Fill out your copyright notice in the Description page of Project Settings.


#include "FireworksPawn.h"

// Sets default values
AFireworksPawn::AFireworksPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = PawnRoot;
	CameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Camera Root"));
	CameraRoot->SetupAttachment(PawnRoot);
	VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VR Camera"));
	VRCamera->SetupAttachment(CameraRoot);

	MotionControllerR = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionControllerR"));
	MotionControllerR->SetupAttachment(PawnRoot);
	MotionControllerR->MotionSource = FName(TEXT("Right"));
	MotionControllerL = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionControllerL"));
	MotionControllerL->SetupAttachment(PawnRoot);
	MotionControllerL->MotionSource = FName(TEXT("Left"));

	LeftHandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftHandMesh"));
	LeftHandMesh->SetupAttachment(MotionControllerL);
	RightHandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightHandMesh"));
	RightHandMesh->SetupAttachment(MotionControllerR);

	RightHandCollision = CreateDefaultSubobject<USphereComponent>(TEXT("RightHandCollision"));
	RightHandCollision->SetupAttachment(RightHandMesh);
	RightHandCollision->SetSphereRadius(10.0f, false);
	LeftHandCollision = CreateDefaultSubobject<USphereComponent>(TEXT("LeftHandCollision"));
	LeftHandCollision->SetupAttachment(LeftHandMesh);
	LeftHandCollision->SetSphereRadius(10.0f, false);

	WidgetInteractionL = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WidgetInteraction_L"));
	WidgetInteractionL->SetupAttachment(LeftHandMesh);
	WidgetInteractionR = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WidgetInteraction_R"));
	WidgetInteractionR->SetupAttachment(RightHandMesh);

	LaserL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaserL"));
	LaserL->SetupAttachment(WidgetInteractionL);
	LaserR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaserR"));
	LaserR->SetupAttachment(WidgetInteractionR);

}

// Sample Hand Velocities for throw approximation
void AFireworksPawn::SampleHandVelocities()
{
	// Left hand
	if (IsGrabbingL)
	{
		VelocitySamples_L.Add(LeftHandCollision->GetPhysicsLinearVelocity());
		if (VelocitySamples_L.Num() > VelocitySamples)
		{
			VelocitySamples_L.RemoveAt(0, 1, true);
		}
	}

	// Right hand
	if (IsGrabbingR)
	{
		VelocitySamples_R.Add(RightHandCollision->GetPhysicsLinearVelocity());
		if (VelocitySamples_R.Num() > VelocitySamples)
		{
			VelocitySamples_R.RemoveAt(0, 1, true);
		}
	}
}

// Called when the game starts or when spawned
void AFireworksPawn::BeginPlay()
{
	Super::BeginPlay();
	
	CameraRoot->AttachToComponent(PawnRoot, FAttachmentTransformRules::KeepRelativeTransform);
	VRCamera->AttachToComponent(CameraRoot, FAttachmentTransformRules::KeepRelativeTransform);
	MotionControllerR->AttachToComponent(PawnRoot, FAttachmentTransformRules::KeepRelativeTransform);
	MotionControllerL->AttachToComponent(PawnRoot, FAttachmentTransformRules::KeepRelativeTransform);
	LeftHandMesh->AttachToComponent(MotionControllerL, FAttachmentTransformRules::KeepRelativeTransform);
	RightHandMesh->AttachToComponent(MotionControllerR, FAttachmentTransformRules::KeepRelativeTransform);
	RightHandCollision->AttachToComponent(RightHandMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	LeftHandCollision->AttachToComponent(LeftHandMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	WidgetInteractionL->AttachToComponent(LeftHandMesh, FAttachmentTransformRules::KeepRelativeTransform);
	WidgetInteractionR->AttachToComponent(RightHandMesh, FAttachmentTransformRules::KeepRelativeTransform);
	LaserL->AttachToComponent(WidgetInteractionL, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	LaserR->AttachToComponent(WidgetInteractionR, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

// Called every frame
void AFireworksPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SampleHandVelocities();
	TryUpdateLasers();
}

// Called to bind functionality to input
void AFireworksPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Setup grab attachment
void AFireworksPawn::SetupGrabAttachment(EControllerHand Hand) {
	FName Socket = Hand == EControllerHand::Left ? TEXT("SocketL") : TEXT("SocketR");
	APickableObject* HeldObject = Hand == EControllerHand::Left ? HeldObject_L : HeldObject_R;
	USkeletalMeshComponent* HandMesh = Hand == EControllerHand::Left ? LeftHandMesh : RightHandMesh;

	FTransform HeldObjectTransformLocal = HeldObject->StaticMesh->GetSocketTransform(Socket, ERelativeTransformSpace::RTS_Actor);

	// Set new values
	FTransform NewTransform;
	NewTransform.SetScale3D(FVector(1.f, 1.f, 1.f));
	NewTransform.SetLocation(IsSteamVR ? FVector(-10.f, 0.f, 0.f) : FVector(0.f, 0.f, 0.f));
	NewTransform.SetRotation(HeldObjectTransformLocal.GetRotation().Inverse());

	// Set new transform
	HeldObject->SetActorRelativeTransform(NewTransform);
	HeldObject->AddActorLocalOffset(HeldObjectTransformLocal.GetLocation() * -1.f);
}

// Try grab
bool AFireworksPawn::TryGrab(EControllerHand Hand)
{
	if (Hand == EControllerHand::Left) {
		// Left hand
		if (IsValid(HeldObject_L)) {
			return false;
		}
		if (!IsValid(HoveredActorL)) {
			return false;
		}
		HoveredActorL->StaticMesh->SetSimulatePhysics(false);
		HoveredActorL->StaticMesh->SetRenderCustomDepth(false);
		HeldObject_L = HoveredActorL;
		HeldObject_L->AttachToComponent(MotionControllerL, FAttachmentTransformRules::KeepWorldTransform);
		SetupGrabAttachment(EControllerHand::Left);
		HeldObject_L->SetInstigator(this);
		IsGrabbingL = true;

		return true;
	}
	else {
		// Right hand
		if (IsValid(HeldObject_R)) {
			return false;
		}
		if (!IsValid(HoveredActorR)) {
			return false;
		}
		HoveredActorR->StaticMesh->SetSimulatePhysics(false);
		HoveredActorR->StaticMesh->SetRenderCustomDepth(false);
		HeldObject_R = HoveredActorR;
		HeldObject_R->AttachToComponent(MotionControllerR, FAttachmentTransformRules::KeepWorldTransform);
		SetupGrabAttachment(EControllerHand::Right);
		HeldObject_R->SetInstigator(this);
		IsGrabbingR = true;

		return true;
	}
}

// Approximate Throw Velocity
FVector AFireworksPawn::ApproximateThrowVelocity(EControllerHand Hand)
{
	TArray<FVector> SampledVelocities = Hand == EControllerHand::Left ? VelocitySamples_L : VelocitySamples_R;
	FVector ApproximatedVelocity;

	if (!SampledVelocities.IsEmpty()) {
		// TODO: discard shortest and longest vector, but first check if average works

		// Calculate arithmetic average of Sampled Velocities
		for (int32 i = 0; i < SampledVelocities.Num(); i++)
		{
			ApproximatedVelocity += SampledVelocities[i];

			// Draw debug lines
			if (DrawApproximationDebug)
			{
				FVector StartLoc = Hand == EControllerHand::Left ? LeftHandMesh->GetComponentLocation() : RightHandMesh->GetComponentLocation();
				DrawDebugLine(GetWorld(), StartLoc, StartLoc + SampledVelocities[i], FColor::Magenta, false, 2.f);
			}
		}
		ApproximatedVelocity = ApproximatedVelocity / SampledVelocities.Num();
	}

	// Draw final result debug
	if (DrawApproximationDebug)
	{
		FVector StartLoc = Hand == EControllerHand::Left ? LeftHandMesh->GetComponentLocation() : RightHandMesh->GetComponentLocation();
		DrawDebugLine(GetWorld(), StartLoc, StartLoc + ApproximatedVelocity, FColor::Green, false, 2.f);
	}

	return ApproximatedVelocity;
}

// Throw object
void AFireworksPawn::ThrowObject(APickableObject* Object, EControllerHand Hand)
{
	Object->ThrowingHand = Hand;
	Object->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Object->StaticMesh->SetSimulatePhysics(true);
	if (!Object->IsRocket) {
		Object->StaticMesh->SetPhysicsLinearVelocity(ApproximateThrowVelocity(Hand) * ThrowVelocityMultiplier);
	}
	Object->ThrowEffects();
}

// Drop
bool AFireworksPawn::Drop(EControllerHand Hand)
{
	if (Hand == EControllerHand::Left) {
		// Left hand
		if (IsValid(HeldObject_L)) {
			ThrowObject(HeldObject_L, Hand);

			HeldObject_L = nullptr;
			IsGrabbingL = false;
		}
		else {
			return false;
		}
	}
	else {
		// Right hand
		if (IsValid(HeldObject_R)) {
			ThrowObject(HeldObject_R, Hand);

			HeldObject_R = nullptr;
			IsGrabbingR = false;
		}
		else {
			return false;
		}
	}

	return true;
}

// Enable laser on specific hand
void AFireworksPawn::EnableLaserOnHand(EControllerHand Hand)
{
	if (Hand == EControllerHand::Left)
	{
		TryShowLaserL = true;
	}
	else {
		TryShowLaserR = true;
	}
}

// Disable laser on hand
void AFireworksPawn::DisableLaserOnHand(EControllerHand Hand)
{
	if (Hand == EControllerHand::Left)
	{
		TryShowLaserL = false;
		LaserL->SetHiddenInGame(true);
	}
	else {
		TryShowLaserR = false;
		LaserR->SetHiddenInGame(true);
	}
}

// Update laser visuals and trace
void AFireworksPawn::TryUpdateLasers()
{
		// --- Left Hand ---
		if (TryShowLaserL)
		{
			FVector StartLocation = LaserL->GetComponentLocation();
			FVector EndLocation = StartLocation + (WidgetInteractionL->GetForwardVector() * WidgetInteractionL->InteractionDistance);
			GetWorld()->LineTraceSingleByChannel(CurrentLaserHitL, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility);
			LaserL->SetHiddenInGame(false);
			LaserL->SetRelativeScale3D(FVector((CurrentLaserHitL.bBlockingHit ? CurrentLaserHitL.Distance / 5 : 1000.0f), LaserL->GetRelativeScale3D().Y, LaserL->GetRelativeScale3D().Z));
		} 

	// --- Right Hand ---
		if (TryShowLaserR)
		{
			FVector StartLocation = LaserR->GetComponentLocation();
			FVector EndLocation = StartLocation + (WidgetInteractionR->GetForwardVector() * WidgetInteractionR->InteractionDistance);
			GetWorld()->LineTraceSingleByChannel(CurrentLaserHitR, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility);
			LaserR->SetHiddenInGame(false);
			LaserR->SetRelativeScale3D(FVector((CurrentLaserHitR.bBlockingHit ? CurrentLaserHitR.Distance / 5 : 1000.0f), LaserR->GetRelativeScale3D().Y, LaserR->GetRelativeScale3D().Z));
		} 
}