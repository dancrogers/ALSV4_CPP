// Project:         Advanced Locomotion System V4 on C++
// Copyright:       Copyright (C) 2020 Doğa Can Yanıkoğlu
// License:         MIT License (http://www.opensource.org/licenses/mit-license.php)
// Source Code:     https://github.com/dyanikoglu/ALSV4_CPP
// Original Author: Doğa Can Yanıkoğlu
// Contributors:

#pragma once

#include "CoreMinimal.h"
#include "ALSCharacterEnumLibrary.generated.h"

/* Returns the enumeration index. */
template <typename Enumeration>
static FORCEINLINE int32 GetEnumerationIndex(const Enumeration InValue)
{
	return StaticEnum<Enumeration>()->GetIndexByValue(static_cast<int64>(InValue));
}

/* Returns the enumeration value as string. */
template <typename Enumeration>
static FORCEINLINE FString GetEnumerationToString(const Enumeration InValue)
{
	return StaticEnum<Enumeration>()->GetNameStringByValue(static_cast<int64>(InValue));
}

UENUM(BlueprintType, Category = "ALS|CharacterEnumLibrary")
enum class EALSGait : uint8
{
	Walking,
	Running,
	Sprinting
};

UENUM(BlueprintType, Category = "ALS|CharacterEnumLibrary")
enum class EALSMovementAction : uint8
{
	None,
	LowMantle,
	HighMantle,
	Rolling,
	GettingUp
};

UENUM(BlueprintType, Category = "ALS|CharacterEnumLibrary")
enum class EALSMovementState : uint8
{
	None,
	Grounded,
	InAir,
	Mantling,
	Ragdoll
};

UENUM(BlueprintType, Category = "ALS|CharacterEnumLibrary")
enum class EALSOverlayState : uint8
{
	Default,
	Masculine,
	Feminine,
	Injured,
	HandsTied,
	Rifle,
	PistolOneHanded,
	PistolTwoHanded,
	Bow,
	Torch,
	Binoculars,
	Box,
	Barrel,
	SwordAndShield
};

UENUM(BlueprintType, Category = "ALS|CharacterEnumLibrary")
enum class EALSRotationMode : uint8
{
	VelocityDirection,
	LookingDirection,
	Aiming
};

UENUM(BlueprintType, Category = "ALS|CharacterEnumLibrary")
enum class EALSStance : uint8
{
	Standing,
	Crouching
};

UENUM(BlueprintType, Category = "ALS|CharacterEnumLibrary")
enum class EALSViewMode : uint8
{
	ThirdPerson,
	FirstPerson
};

UENUM(BlueprintType, Category = "ALS|CharacterEnumLibrary")
enum class EALSAnimFeatureExample : uint8
{
	StrideBlending,
	AdditiveBlending,
	SprintImpulse
};

UENUM(BlueprintType, Category = "ALS|CharacterEnumLibrary")
enum class EALSFootstepType : uint8
{
	Step,
	WalkRun,
	Jump,
	Land
};

UENUM(BlueprintType, Category = "ALS|CharacterEnumLibrary")
enum class EALSGroundedEntryState : uint8
{
	None,
	Roll
};

UENUM(BlueprintType, Category = "ALS|CharacterEnumLibrary")
enum class EALSHipsDirection : uint8
{
	F,
	B,
	RF,
	RB,
	LF,
	LB
};

UENUM(BlueprintType, Category = "ALS|CharacterEnumLibrary")
enum class EALSMantleType : uint8
{
	HighMantle,
	LowMantle,
	FallingCatch
};

UENUM(BlueprintType, Category = "ALS|CharacterEnumLibrary")
enum class EALSMovementDirection : uint8
{
	Forward,
	Right,
	Left,
	Backward
};
