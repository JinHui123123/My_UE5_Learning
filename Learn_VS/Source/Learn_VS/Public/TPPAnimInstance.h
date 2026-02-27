// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TPPAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_VS_API UTPPAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float detetime) override;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "AnimaValue")
	class APlayerCharacter* PlayerCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "AnimaValue")
	float Speed; 

	UPROPERTY(BlueprintReadOnly, Category = "AnimaValue")
	float deirection;

	UPROPERTY(BlueprintReadOnly, Category = "AnimaValue")
	bool isFalling;
};
