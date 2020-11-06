// Project:         Advanced Locomotion System V4 on C++
// Copyright:       Copyright (C) 2020 Doğa Can Yanıkoğlu
// License:         MIT License (http://www.opensource.org/licenses/mit-license.php)
// Source Code:     https://github.com/dyanikoglu/ALSV4_CPP
// Original Author: Doğa Can Yanıkoğlu
// Contributors:

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Library/ALSCharacterEnumLibrary.h"

#include "ALSCharacterStructLibrary.generated.h"

class UCurveVector;
class UAnimMontage;
class UAnimSequenceBase;
class UCurveFloat;

USTRUCT(BlueprintType, Category = "ALS|CharacterStructLibrary")
struct FALSComponentAndTransform
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	FTransform Transform;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	class UPrimitiveComponent *Component = nullptr;
};

USTRUCT(BlueprintType, Category = "ALS|CharacterStructLibrary")
struct FALSCameraSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	float TargetArmLength = 0.0f;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	FVector SocketOffset;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	float LagSpeed = 0.0f;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	float RotationLagSpeed = 0.0f;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	bool bDoCollisionTest = true;
};

USTRUCT(BlueprintType, Category = "ALS|CharacterStructLibrary")
struct FALSCameraGaitSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	FALSCameraSettings Walking;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	FALSCameraSettings Running;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	FALSCameraSettings Sprinting;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	FALSCameraSettings Crouching;
};

USTRUCT(BlueprintType, Category = "ALS|CharacterStructLibrary")
struct FALSCameraStateSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	FALSCameraGaitSettings VelocityDirection;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	FALSCameraGaitSettings LookingDirection;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	FALSCameraGaitSettings Aiming;
};

USTRUCT(BlueprintType, Category = "ALS|CharacterStructLibrary")
struct FALSMantleAsset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	UAnimMontage *AnimMontage = nullptr;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	UCurveVector *PositionCorrectionCurve = nullptr;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	FVector StartingOffset;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	float LowHeight = 0.0f;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	float LowPlayRate = 0.0f;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	float LowStartPosition = 0.0f;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	float HighHeight = 0.0f;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	float HighPlayRate = 0.0f;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	float HighStartPosition = 0.0f;
};

USTRUCT(BlueprintType, Category = "ALS|CharacterStructLibrary")
struct FALSMantleParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	UAnimMontage *AnimMontage = nullptr;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	UCurveVector *PositionCorrectionCurve = nullptr;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	float StartingPosition = 0.0f;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	float PlayRate = 0.0f;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	FVector StartingOffset;
};

USTRUCT(BlueprintType, Category = "ALS|CharacterStructLibrary")
struct FALSMantleTraceSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	float MaxLedgeHeight = 0.0f;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	float MinLedgeHeight = 0.0f;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	float ReachDistance = 0.0f;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	float ForwardTraceRadius = 0.0f;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	float DownwardTraceRadius = 0.0f;
};

USTRUCT(BlueprintType, Category = "ALS|CharacterStructLibrary")
struct FALSMovementSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	float WalkSpeed = 0.0f;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	float RunSpeed = 0.0f;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	float SprintSpeed = 0.0f;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	UCurveVector *MovementCurve = nullptr;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	UCurveFloat *RotationRateCurve = nullptr;

	float GetSpeedForGait(EALSGait Gait)
	{
		switch (Gait)
		{
		case EALSGait::Running:
			return RunSpeed;
		case EALSGait::Sprinting:
			return SprintSpeed;
		case EALSGait::Walking:
			return WalkSpeed;
		default:
			return RunSpeed;
		}
	}
};

USTRUCT(BlueprintType, Category = "ALS|CharacterStructLibrary")
struct FALSMovementStanceSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	FALSMovementSettings Standing;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	FALSMovementSettings Crouching;
};

USTRUCT(BlueprintType, Category = "ALS|CharacterStructLibrary")
struct FALSMovementStateSettings : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	FALSMovementStanceSettings VelocityDirection;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	FALSMovementStanceSettings LookingDirection;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	FALSMovementStanceSettings Aiming;
};

USTRUCT(BlueprintType, Category = "ALS|CharacterStructLibrary")
struct FALSRotateInPlaceAsset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	UAnimSequenceBase *Animation = nullptr;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	FName SlotName;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	float SlowTurnRate = 90.0f;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	float FastTurnRate = 90.0f;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	float SlowPlayRate = 1.0f;

	UPROPERTY(EditAnywhere, Category = "ALS|CharacterStructLibrary")
	float FastPlayRate = 1.0f;
};
