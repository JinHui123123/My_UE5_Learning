// Fill out your copyright notice in the Description page of Project Settings.


#include "MorphComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values for this component's properties
UMorphComponent::UMorphComponent()
{
	PrimaryComponentTick.bCanEverTick = false; // 本例无需每帧Tick
	CurrentState = EMorphState::MS_Solid; // 默认固态
}


// Called when the game starts
void UMorphComponent::BeginPlay()
{
	Super::BeginPlay();

	ApplySolidState();
	
}
// === 公开的切换函数 ===
void UMorphComponent::SwitchToSolid() { if (bCanMorph) SwitchState(EMorphState::MS_Solid); }
void UMorphComponent::SwitchToLiquid() { if (bCanMorph) SwitchState(EMorphState::MS_Liquid); }
void UMorphComponent::SwitchToGas() { if (bCanMorph) SwitchState(EMorphState::MS_Gas); }

// === 核心切换逻辑 ===
void UMorphComponent::SwitchState(EMorphState NewState)
{
    if (CurrentState == NewState || !bCanMorph) return;

    CurrentState = NewState;
    bCanMorph = false;
    GetWorld()->GetTimerManager().SetTimer(MorphCooldownTimerHandle, this, &UMorphComponent::EndMorphCooldown, MorphCooldownDuration, false);

    // 根据新状态应用不同的移动和碰撞参数
    switch (CurrentState)
    {
    case EMorphState::MS_Solid: ApplySolidState(); break;
    case EMorphState::MS_Liquid: ApplyLiquidState(); break;
    case EMorphState::MS_Gas: ApplyGasState(); break;
    }

    // 广播状态改变事件，蓝图将接收此事件并更新材质等
    OnMorphStateChanged.Broadcast(CurrentState);
    // 修改为更简洁的中文输出：
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan,
        FString::Printf(TEXT("ModeChange: %s"),
            *UEnum::GetDisplayValueAsText(CurrentState).ToString()));

}

void UMorphComponent::EndMorphCooldown()
{
    bCanMorph = true;
}

// === 差异化移动/碰撞实现 ===
void UMorphComponent::ApplySolidState()
{
    ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
    if (!OwnerCharacter) return;

    UCharacterMovementComponent* MoveComp = OwnerCharacter->GetCharacterMovement();
    UCapsuleComponent* CapsuleComp = OwnerCharacter->GetCapsuleComponent();

    // 重置为“正常”角色参数
    MoveComp->MaxWalkSpeed = 600.f;
    MoveComp->JumpZVelocity = 420.f;
    MoveComp->GravityScale = 1.0f;
    MoveComp->bCanWalkOffLedges = true;
    MoveComp->SetMovementMode(MOVE_Walking);

    // 设置碰撞预设为 Pawn
    CapsuleComp->SetCollisionProfileName(FName("Pawn"));
    CapsuleComp->SetCapsuleHalfHeight(88.f); // 恢复默认高度
    CapsuleComp->SetCapsuleRadius(34.f);
}

void UMorphComponent::ApplyLiquidState()
{
    ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
    if (!OwnerCharacter) return;

    UCharacterMovementComponent* MoveComp = OwnerCharacter->GetCharacterMovement();
    UCapsuleComponent* CapsuleComp = OwnerCharacter->GetCapsuleComponent();

    // 液态：移动慢，无跳跃，可爬行
    MoveComp->MaxWalkSpeed = 200.f;
    MoveComp->JumpZVelocity = 0.f;
    MoveComp->GravityScale = 0.5f; // 稍轻一点
    MoveComp->bCanWalkOffLedges = false;

    // 关键：缩小胶囊体以穿过低矮缝隙
    // 可以设置一个自定义的“NoCollision”预设，或临时禁用碰撞（需谨慎）
    // 简单演示：改为忽略所有动态物体，只阻挡世界静态
    CapsuleComp->SetCapsuleHalfHeight(20.f); // 变得很扁
    CapsuleComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
    CapsuleComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Ignore);
}

void UMorphComponent::ApplyGasState()
{
    ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
    if (!OwnerCharacter) return;

    UCharacterMovementComponent* MoveComp = OwnerCharacter->GetCharacterMovement();
    UCapsuleComponent* CapsuleComp = OwnerCharacter->GetCapsuleComponent();

    // 气态：可浮空/滑翔，重力小，但移动控制弱
    MoveComp->MaxWalkSpeed = 300.f;
    MoveComp->JumpZVelocity = 0.f;
    MoveComp->GravityScale = 0.2f; // 非常轻
    MoveComp->AirControl = 0.8f; // 高空中控制能力强
    // 进入滑翔/浮空状态
    MoveComp->SetMovementMode(MOVE_Falling); // 强制进入下落状态，但因重力小会缓慢下降

    // 恢复碰撞，但可能对风有特殊响应（可通过重叠检测实现“怕风”）
    CapsuleComp->SetCollisionProfileName(FName("Pawn"));
    CapsuleComp->SetCapsuleHalfHeight(88.f);
}

