// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MorphComponent.generated.h"


// 1. 定义形态枚举
UENUM(BlueprintType)
enum class EMorphState : uint8
{
	MS_Solid      UMETA(DisplayName = "Solid"),
	MS_Liquid     UMETA(DisplayName = "Liquid"),
	MS_Gas        UMETA(DisplayName = "Gas")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEARN_VS_API UMorphComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMorphComponent();

	// 2. 可供蓝图调用的切换函数
	UFUNCTION(BlueprintCallable, Category = "Morph")
	void SwitchToSolid();
	UFUNCTION(BlueprintCallable, Category = "Morph")
	void SwitchToLiquid();
	UFUNCTION(BlueprintCallable, Category = "Morph")
	void SwitchToGas();

	// 3. 获取当前形态
	UFUNCTION(BlueprintPure, Category = "Morph")
	EMorphState GetCurrentState() const { return CurrentState; }
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// 4. 内部切换实现
	void SwitchState(EMorphState NewState);

	// 5. 修改角色移动和碰撞参数的函数
	void ApplySolidState();
	void ApplyLiquidState();
	void ApplyGasState();

private:
	// 6. 状态变量
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Morph", meta = (AllowPrivateAccess = "true"))
	EMorphState CurrentState;

	// 7. 切换冷却相关
	UPROPERTY(EditDefaultsOnly, Category = "Morph")
	float MorphCooldownDuration = 0.5f;
	bool bCanMorph = true;
	FTimerHandle MorphCooldownTimerHandle;
	void EndMorphCooldown();

public:	
	// 8. 声明一个动态多播委托，用于通知蓝图形态已改变
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMorphStateChanged, EMorphState, NewState);
	UPROPERTY(BlueprintAssignable, Category = "Morph")
	FOnMorphStateChanged OnMorphStateChanged;
		
};
