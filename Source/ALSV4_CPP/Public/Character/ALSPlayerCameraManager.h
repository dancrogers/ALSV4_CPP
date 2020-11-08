// Project:         Advanced Locomotion System V4 on C++
// Copyright:       Copyright (C) 2020 Doğa Can Yanıkoğlu
// License:         MIT License (http://www.opensource.org/licenses/mit-license.php)
// Source Code:     https://github.com/dyanikoglu/ALSV4_CPP
// Original Author: Doğa Can Yanıkoğlu
// Contributors:

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "ALSPlayerCameraManager.generated.h"

class AALSBaseCharacter;

/**
 * Player camera manager class
 */
UCLASS(Blueprintable, BlueprintType)
class ALSV4_CPP_API AALSPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	AALSPlayerCameraManager();

	UFUNCTION(BlueprintCallable, Category = "ALVS_V4|PlayerCameraManager")
	void OnPossess(AALSBaseCharacter *NewCharacter);

	UFUNCTION(BlueprintCallable, Category = "ALVS_V4|PlayerCameraManager")
	float GetCameraBehaviorParam(FName CurveName) const;

	/** Implement debug logic in BP */
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "ALVS_V4|PlayerCameraManager")
	void DrawDebugTargets(FVector PivotTargetLocation);

protected:
	virtual void UpdateViewTargetInternal(FTViewTarget &OutVT, float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "ALVS_V4|PlayerCameraManager")
	static FVector CalculateAxisIndependentLag(
		FVector CurrentLocation, FVector TargetLocation, FRotator CameraRotation, FVector LagSpeeds, float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "ALVS_V4|PlayerCameraManager")
	bool CustomCameraBehavior(float DeltaTime, FVector &Location, FRotator &Rotation, float &FOV);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ALVS_V4|PlayerCameraManager")
	AALSBaseCharacter *ControlledCharacter = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ALVS_V4|PlayerCameraManager")
	USkeletalMeshComponent *CameraBehavior = nullptr;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALVS_V4|PlayerCameraManager")
	FVector RootLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALVS_V4|PlayerCameraManager")
	FTransform SmoothedPivotTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALVS_V4|PlayerCameraManager")
	FVector PivotLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALVS_V4|PlayerCameraManager")
	FVector TargetCameraLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALVS_V4|PlayerCameraManager")
	FRotator TargetCameraRotation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ALVS_V4|PlayerCameraManager")
	FRotator DebugViewRotation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ALVS_V4|PlayerCameraManager")
	FVector DebugViewOffset;
};
