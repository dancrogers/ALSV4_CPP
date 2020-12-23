// Project:         Advanced Locomotion System V4 on C++
// Source Code:     https://github.com/dyanikoglu/ALSV4_CPP
// Original Author: Haziq Fadhil
// Contributors:    Doga Can Yanikoglu

#include "Character/ALSCharacterMovementComponent.h"
#include "Character/ALSBaseCharacter.h"

UALSCharacterMovementComponent::UALSCharacterMovementComponent(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
	DodgeStrength = 500.f;
}

void UALSCharacterMovementComponent::OnMovementUpdated(float DeltaTime, const FVector &OldLocation, const FVector &OldVelocity)
{
	Super::OnMovementUpdated(DeltaTime, OldLocation, OldVelocity);

	if (!CharacterOwner)
	{
		return;
	}

	// Movespeed
	if (bRequestMovementSettingsChange)
	{
		MaxWalkSpeed = MyNewMaxWalkSpeed;
		MaxWalkSpeedCrouched = MyNewMaxWalkSpeed;
	}

	//Dodge
	if (bWantsToDodge)
	{
		bWantsToDodge = false;

		//Only dodge if on the ground (in the air causes problems trying to get the two modes to line up due to friction)
		if (IsMovingOnGround())
		{
			MoveDirection.Normalize();
			FVector DodgeVelocity = MoveDirection * DodgeStrength;
			//Set Z component to zero so we don't go up
			DodgeVelocity.Z = 0.0f;

			Launch(DodgeVelocity);
		}
	}

	//Predicted Launch
	if (bWantsToLaunch)
	{
		bWantsToLaunch = false;
		Launch(LaunchVector);
	}
}

// Override of base CMC launch -- different than our predicted launch
bool UALSCharacterMovementComponent::HandlePendingLaunch()
{
	if (!PendingLaunchVelocity.IsZero() && HasValidData())
	{
		Velocity = PendingLaunchVelocity;
		//Remmed out so our dodge move won't play the falling animation.
		if (Velocity.Z > 0.0f)
		{
			SetMovementMode(MOVE_Falling);
		}
		PendingLaunchVelocity = FVector::ZeroVector;
		bForceNextFloorCheck = true;
		return true;
	}

	return false;
}

void UALSCharacterMovementComponent::UpdateFromCompressedFlags(uint8 Flags) // Client only
{
	Super::UpdateFromCompressedFlags(Flags);

	bRequestMovementSettingsChange = (Flags & FSavedMove_Character::FLAG_Custom_0) != 0;
	bWantsToDodge = (Flags & FSavedMove_Character::FLAG_Custom_1) != 0;
	bWantsToLaunch = (Flags & FSavedMove_Character::FLAG_Custom_2) != 0;
}

class FNetworkPredictionData_Client *UALSCharacterMovementComponent::GetPredictionData_Client() const
{
	check(PawnOwner != nullptr);

	if (!ClientPredictionData)
	{
		UALSCharacterMovementComponent *MutableThis = const_cast<UALSCharacterMovementComponent *>(this);

		MutableThis->ClientPredictionData = new FNetworkPredictionData_Client_My(*this);
		MutableThis->ClientPredictionData->MaxSmoothNetUpdateDist = 92.f;
		MutableThis->ClientPredictionData->NoSmoothNetUpdateDist = 140.f;
	}

	return ClientPredictionData;
}

void UALSCharacterMovementComponent::FSavedMove_My::Clear()
{
	Super::Clear();

	bSavedRequestMovementSettingsChange = false;
	bSavedWantsToDodge = false;
	bSavedWantsToLaunch = false;
	SavedMoveDirection = FVector::ZeroVector;
	SavedLaunchVector = FVector::ZeroVector;
}

uint8 UALSCharacterMovementComponent::FSavedMove_My::GetCompressedFlags() const
{
	uint8 Result = Super::GetCompressedFlags();

	if (bSavedRequestMovementSettingsChange)
	{
		Result |= FLAG_Custom_0;
	}

	if (bSavedWantsToDodge)
	{
		Result |= FLAG_Custom_1;
	}

	if (bSavedWantsToLaunch)
	{
		Result |= FLAG_Custom_2;
	}

	return Result;
}

bool UALSCharacterMovementComponent::FSavedMove_My::CanCombineWith(const FSavedMovePtr &NewMove, ACharacter *Character, float MaxDelta) const
{
	//Set which moves can be combined together. This will depend on the bit flags that are used.
	if (bSavedRequestMovementSettingsChange != ((FSavedMove_My *)&NewMove)->bSavedRequestMovementSettingsChange)
	{
		return false;
	}
	if (bSavedWantsToDodge != ((FSavedMove_My *)&NewMove)->bSavedWantsToDodge)
	{
		return false;
	}
	if (bSavedWantsToLaunch != ((FSavedMove_My *)&NewMove)->bSavedWantsToLaunch)
	{
		return false;
	}
	if (SavedMoveDirection != ((FSavedMove_My *)&NewMove)->SavedMoveDirection)
	{
		return false;
	}
	if (SavedLaunchVector != ((FSavedMove_My *)&NewMove)->SavedLaunchVector)
	{
		return false;
	}

	return Super::CanCombineWith(NewMove, Character, MaxDelta);
}

void UALSCharacterMovementComponent::FSavedMove_My::SetMoveFor(ACharacter *Character, float InDeltaTime, FVector const &NewAccel,
															   class FNetworkPredictionData_Client_Character &ClientData)
{
	Super::SetMoveFor(Character, InDeltaTime, NewAccel, ClientData);

	UALSCharacterMovementComponent *CharacterMovement = Cast<UALSCharacterMovementComponent>(Character->GetCharacterMovement());
	if (CharacterMovement)
	{
		bSavedRequestMovementSettingsChange = CharacterMovement->bRequestMovementSettingsChange;
		bSavedWantsToDodge = CharacterMovement->bWantsToDodge;
		bSavedWantsToLaunch = CharacterMovement->bWantsToLaunch;
		SavedMoveDirection = CharacterMovement->MoveDirection;
		SavedLaunchVector = CharacterMovement->LaunchVector;
	}
}

void UALSCharacterMovementComponent::FSavedMove_My::PrepMoveFor(class ACharacter *Character)
{
	Super::PrepMoveFor(Character);

	UALSCharacterMovementComponent *CharacterMovement = Cast<UALSCharacterMovementComponent>(Character->GetCharacterMovement());
	if (CharacterMovement)
	{
		CharacterMovement->MoveDirection = SavedMoveDirection;
		CharacterMovement->LaunchVector = SavedLaunchVector;
	}
}

UALSCharacterMovementComponent::FNetworkPredictionData_Client_My::FNetworkPredictionData_Client_My(
	const UCharacterMovementComponent &ClientMovement)
	: Super(ClientMovement)
{
}

FSavedMovePtr UALSCharacterMovementComponent::FNetworkPredictionData_Client_My::AllocateNewMove()
{
	return MakeShared<FSavedMove_My>();
}

//Set Max Walk Speed RPC to transfer the current Max Walk Speed from the Owning Client to the Server
bool UALSCharacterMovementComponent::Server_SetMaxWalkingSpeed_Validate(const float NewMaxWalkSpeed)
{
	if (NewMaxWalkSpeed < 0.f || NewMaxWalkSpeed > 2000.f)
		return false;
	else
		return true;
}

void UALSCharacterMovementComponent::Server_SetMaxWalkingSpeed_Implementation(const float NewMaxWalkSpeed)
{
	MyNewMaxWalkSpeed = NewMaxWalkSpeed;
}

void UALSCharacterMovementComponent::SetMaxWalkingSpeed(float NewMaxWalkSpeed)
{
	if (PawnOwner->IsLocallyControlled())
	{
		MyNewMaxWalkSpeed = NewMaxWalkSpeed;
		Server_SetMaxWalkingSpeed(NewMaxWalkSpeed);
	}
	bRequestMovementSettingsChange = true;
}

// Dodge ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Dodge RPC to transfer the current Move Direction from the Owning Client to the Server
bool UALSCharacterMovementComponent::Server_MoveDirection_Validate(const FVector &MoveDir)
{
	return true;
}

void UALSCharacterMovementComponent::Server_MoveDirection_Implementation(const FVector &MoveDir)
{
	MoveDirection = MoveDir;
}

//Trigger the Dodge ability on the Owning Client
void UALSCharacterMovementComponent::Dodge()
{
	if (PawnOwner->IsLocallyControlled())
	{
		MoveDirection = PawnOwner->GetLastMovementInputVector();
		Server_MoveDirection(MoveDirection);
	}

	bWantsToDodge = true;
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END Dodge

//Launch ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool UALSCharacterMovementComponent::Server_SetLaunchVector_Validate(const FVector &LaunchVec)
{
	return (LaunchVec.Size() >= 0.f && LaunchVec.Size() <= 20000.f);
}

//Launch RPC to transfer the current Launch Vector from the Owning Client to the Server
void UALSCharacterMovementComponent::Server_SetLaunchVector_Implementation(const FVector &LaunchVec)
{
	LaunchVector = LaunchVec;
}

//Trigger the Dodge ability on the Owning Client
void UALSCharacterMovementComponent::PredictedLaunch(const FVector &LaunchVec)
{
	if (PawnOwner->IsLocallyControlled())
	{
		LaunchVector = LaunchVec;
		Server_SetLaunchVector(LaunchVector);
	}

	bWantsToLaunch = true;
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END Launch
