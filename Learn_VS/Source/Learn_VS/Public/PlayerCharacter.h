// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_VS_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

	public:
		//声明构造函数
		APlayerCharacter();
	
	protected:
		virtual void BeginPlay() override;

	public:
		virtual void Tick(float DeltaTime) override;

		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
