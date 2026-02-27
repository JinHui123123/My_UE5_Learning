// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPAnimInstance.h"
#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UTPPAnimInstance::NativeInitializeAnimation()
{
	PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());
}

void UTPPAnimInstance::NativeUpdateAnimation(float detetime)
{
	if (PlayerCharacter)
	{
		FVector velocity = PlayerCharacter->GetVelocity();

		Speed = velocity.Length();

		FRotator rotator = PlayerCharacter->GetActorRotation();

		deirection = CalculateDirection(velocity, rotator);   

		UCharacterMovementComponent* movement = PlayerCharacter->GetCharacterMovement();

		isFalling = movement->IsFalling();

	}
}
