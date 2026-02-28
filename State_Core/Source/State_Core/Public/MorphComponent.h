// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MorphComponent.generated.h"


// 1. 定义形态枚举
UENUM(BlueprintType)  // 告诉UE这个枚举可以在蓝图中使用
enum class EMorphState : uint8  // 使用enum class（C++11强类型枚举），:uint8指定底层类型
{
	MS_Solid      UMETA(DisplayName = "Solid"),     // 固态，在蓝图中显示为"Solid"
	MS_Liquid     UMETA(DisplayName = "Liquid"),    // 液态
	MS_Gas        UMETA(DisplayName = "Gas")        // 气态
};
// 这个枚举定义了角色的三种形态状态，UMETA用于在编辑器和蓝图中提供友好名称

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STATE_CORE_API UMorphComponent : public UActorComponent
{
	GENERATED_BODY()

public:
    UMorphComponent();  // 构造函数声明

    // 2. 可供蓝图调用的切换函数
    UFUNCTION(BlueprintCallable, Category = "Morph")
    // UFUNCTION宏：使C++函数暴露给蓝图
    // BlueprintCallable：蓝图可以调用这个函数
    // Category = "Morph"：在蓝图中这个函数会出现在"Morph"分类下
    void SwitchToSolid();  // 切换到固态
    UFUNCTION(BlueprintCallable, Category = "Morph")
    void SwitchToLiquid(); // 切换到液态
    UFUNCTION(BlueprintCallable, Category = "Morph")
    void SwitchToGas();    // 切换到气态

    // 3. 获取当前形态
    UFUNCTION(BlueprintPure, Category = "Morph")
    // BlueprintPure：这是一个纯函数，不会修改对象状态，可以在蓝图中作为获取节点使用
    EMorphState GetCurrentState() const { return CurrentState; }
    // 内联函数，直接返回CurrentState的值，const表示不修改类成员


protected:
    virtual void BeginPlay() override;  // 重写BeginPlay，组件激活时调用

    // 4. 内部切换实现
    void SwitchState(EMorphState NewState);  // 实际的切换逻辑

    // 5. 修改角色移动和碰撞参数的函数
    void ApplySolidState();   // 应用固态参数
    void ApplyLiquidState();  // 应用液态参数
    void ApplyGasState();     // 应用气态参数
private:
    // 6. 状态变量
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Morph", meta = (AllowPrivateAccess = "true"))
    // UPROPERTY宏：使变量暴露给UE的反射系统
    // VisibleAnywhere：在编辑器的任何地方可见（组件细节面板）
    // BlueprintReadOnly：蓝图可以读取但不能修改
    // meta = (AllowPrivateAccess = "true")：允许在C++中访问这个私有变量
    EMorphState CurrentState;  // 当前形态状态

    // 7. 切换冷却相关
    UPROPERTY(EditDefaultsOnly, Category = "Morph")
    // EditDefaultsOnly：只能在组件默认值中编辑，不能在运行时修改
    float MorphCooldownDuration = 0.5f;  // 切换冷却时间，默认0.5秒

    bool bCanMorph = true;  // 是否可以切换形态，冷却控制标志

    FTimerHandle MorphCooldownTimerHandle;  // UE的定时器句柄，用于管理冷却计时
    void EndMorphCooldown();  // 冷却结束的回调函数
public:
    // 8. 声明一个动态多播委托，用于通知蓝图形态已改变
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMorphStateChanged, EMorphState, NewState);
    // 声明一个动态多播委托，可以带一个参数（新状态），蓝图可以绑定到这个委托

    UPROPERTY(BlueprintAssignable, Category = "Morph")
    // BlueprintAssignable：蓝图可以绑定（Assign）到这个委托
    FOnMorphStateChanged OnMorphStateChanged;  // 委托实例
};