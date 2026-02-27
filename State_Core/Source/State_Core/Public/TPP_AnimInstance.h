// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TPP_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class STATE_CORE_API UTPP_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
protected:
	// 持有玩家指针（在 cpp 中用 Cast 获取）
	UPROPERTY(BlueprintReadOnly, Category = "AnimValues")
	class AMyPlayer* PlayerCharacter;

	// 速度（平面速度）
	UPROPERTY(BlueprintReadOnly, Category = "AnimValues")
	float Speed = 0.0f;

	// 方向（使用 CalculateDirection 计算）
	UPROPERTY(BlueprintReadOnly, Category = "AnimValues")
	float Direction = 0.0f;

	// 是否在空中（遵循 UE 命名习惯）
	UPROPERTY(BlueprintReadOnly, Category = "AnimValues")
	bool bIsFalling = false;

	// 是否在地面（遵循 UE 命名习惯）
	UPROPERTY(BlueprintReadOnly, Category = "AnimValues")
	float ZSpeed = 0.0f; // 垂直速度
};
