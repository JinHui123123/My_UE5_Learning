// Fill out your copyright notice in the Description page of Project Settings.


#include "MorphComponent.h"
#include "GameFramework/Character.h"        // 包含Character类，用于获取角色
#include "GameFramework/CharacterMovementComponent.h"  // 包含角色移动组件
#include "Components/CapsuleComponent.h"   // 包含胶囊体组件
// Sets default values for this component's properties
UMorphComponent::UMorphComponent()
{
	PrimaryComponentTick.bCanEverTick = false;  // 设置组件不需要每帧Tick
	CurrentState = EMorphState::MS_Solid;  // 初始化当前状态为固态
}
// 注意：这里只是初始化成员变量，不进行复杂的逻辑

// Called when the game starts
void UMorphComponent::BeginPlay()
{
	Super::BeginPlay();  // 调用父类的BeginPlay
	ApplySolidState();   // 应用初始状态（固态）的参数
	// 这确保角色开始时具有正确的移动和碰撞设置
	
}
// === 公开的切换函数 ===
// 这些是蓝图可以调用的简单包装函数
void UMorphComponent::SwitchToSolid()
{
	if (bCanMorph) SwitchState(EMorphState::MS_Solid);  // 检查冷却，然后切换
}
void UMorphComponent::SwitchToLiquid()
{
	if (bCanMorph) SwitchState(EMorphState::MS_Liquid);
}
void UMorphComponent::SwitchToGas()
{
	if (bCanMorph) SwitchState(EMorphState::MS_Gas);
}

// === 核心切换逻辑 ===
void UMorphComponent::SwitchState(EMorphState NewState)
{
    // 检查：如果已经是目标状态，或者处于冷却中，则直接返回
    if (CurrentState == NewState || !bCanMorph) return;

    // 更新当前状态
    CurrentState = NewState;

    // 开始冷却计时
    bCanMorph = false;  // 设置为不可切换
    GetWorld()->GetTimerManager().SetTimer(
        MorphCooldownTimerHandle,      // 定时器句柄
        this,                          // 回调对象（this）
        &UMorphComponent::EndMorphCooldown,  // 回调函数
        MorphCooldownDuration,         // 延迟时间
        false                          // 不循环，只执行一次
    );

    // 根据新状态应用不同的移动和碰撞参数
    switch (CurrentState)
    {
    case EMorphState::MS_Solid: ApplySolidState(); break;
    case EMorphState::MS_Liquid: ApplyLiquidState(); break; 
    case EMorphState::MS_Gas: ApplyGasState(); break;
    }

    // 广播状态改变事件，蓝图将接收此事件并更新材质等
    OnMorphStateChanged.Broadcast(CurrentState);

    // 屏幕调试信息，开发时用于验证
    GEngine->AddOnScreenDebugMessage(
        -1,           // 键值，-1表示自动分配
        2.0f,         // 显示时间（秒）
        FColor::Cyan, // 颜色（青色）
        FString::Printf(TEXT("Mode Change: %s"), *UEnum::GetValueAsString(CurrentState))
        // 将枚举值转换为字符串并显示
    );
}

// 冷却结束回调
void UMorphComponent::EndMorphCooldown()
{
    bCanMorph = true;  // 重置为可切换状态
}

// === 差异化移动/碰撞实现 ===
// 实现玩法差异的核心部分

void UMorphComponent::ApplySolidState()
{
    // 获取拥有此组件的角色
    ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
    if (!OwnerCharacter) return;  // 安全检查

    // 获取角色的移动组件和胶囊体组件
    UCharacterMovementComponent* MoveComp = OwnerCharacter->GetCharacterMovement();
    UCapsuleComponent* CapsuleComp = OwnerCharacter->GetCapsuleComponent();

    // 重置为"正常"角色参数
    MoveComp->MaxWalkSpeed = 600.f;       // 最大行走速度
    MoveComp->JumpZVelocity = 420.f;      // 跳跃高度
    MoveComp->GravityScale = 1.0f;        // 重力缩放（1.0为默认）
    MoveComp->bCanWalkOffLedges = true;   // 可以从边缘走下来
    MoveComp->SetMovementMode(MOVE_Walking);  // 设置为行走模式

    // 设置碰撞预设为Pawn（标准角色预设）
    CapsuleComp->SetCollisionProfileName(FName("Pawn"));
    // 恢复默认胶囊体尺寸
    CapsuleComp->SetCapsuleHalfHeight(88.f);  // 半高
    CapsuleComp->SetCapsuleRadius(34.f);      // 半径
}

void UMorphComponent::ApplyLiquidState()
{
    ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
    if (!OwnerCharacter) return;

    UCharacterMovementComponent* MoveComp = OwnerCharacter->GetCharacterMovement();
    UCapsuleComponent* CapsuleComp = OwnerCharacter->GetCapsuleComponent();

    // 液态：移动慢，无跳跃，可爬行
    MoveComp->MaxWalkSpeed = 200.f;       // 慢速移动
    MoveComp->JumpZVelocity = 0.f;       // 不能跳跃
    MoveComp->GravityScale = 0.5f;       // 重力减半，有"漂浮"感
    MoveComp->bCanWalkOffLedges = false; // 防止从边缘掉落

    // 关键：缩小胶囊体以穿过低矮缝隙
    CapsuleComp->SetCapsuleHalfHeight(20.f);  // 变得很扁
    // 修改碰撞响应：忽略其他角色和物理物体
    CapsuleComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
    CapsuleComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Ignore);
    // 注意：仍然与世界静态物体碰撞，所以可以在地面上移动
}

void UMorphComponent::ApplyGasState()
{
    ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
    if (!OwnerCharacter) return;

    UCharacterMovementComponent* MoveComp = OwnerCharacter->GetCharacterMovement();
    UCapsuleComponent* CapsuleComp = OwnerCharacter->GetCapsuleComponent();

    // 气态：可浮空/滑翔，重力小，但移动控制弱
    MoveComp->MaxWalkSpeed = 300.f;      // 中等速度
    MoveComp->JumpZVelocity = 0.f;       // 不能跳跃
    MoveComp->GravityScale = 0.2f;       // 重力很小，缓慢下落
    MoveComp->AirControl = 0.8f;         // 高空中控制能力强

    // 进入滑翔/浮空状态
    // 设置为下落模式，但因重力很小会缓慢下降
    MoveComp->SetMovementMode(MOVE_Falling);

    // 恢复碰撞，但可能对风有特殊响应
    CapsuleComp->SetCollisionProfileName(FName("Pawn"));
    CapsuleComp->SetCapsuleHalfHeight(88.f);  // 恢复默认高度
}