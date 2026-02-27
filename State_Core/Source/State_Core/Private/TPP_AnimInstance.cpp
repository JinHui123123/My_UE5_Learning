#include "TPP_AnimInstance.h"
#include "MyPlayer.h"  // 包含你的角色类头文件
#include "GameFramework/CharacterMovementComponent.h"

void UTPP_AnimInstance::NativeInitializeAnimation()
{
    PlayerCharacter = Cast<AMyPlayer>(TryGetPawnOwner());
}

void UTPP_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    if (!PlayerCharacter)
    {
        PlayerCharacter = Cast<AMyPlayer>(TryGetPawnOwner());
    }

    if (PlayerCharacter)
    {
        const FVector Velocity = PlayerCharacter->GetVelocity();
        const FVector Velocity2D = FVector(Velocity.X, Velocity.Y, 0.0f);
        Speed = Velocity2D.Size();

		//获取角色的旋转（通常是 Yaw 角度）并计算方向
        Direction = CalculateDirection(Velocity, PlayerCharacter->GetActorRotation());

		ZSpeed = Velocity.Z; // 获取垂直速度

        if (const UCharacterMovementComponent* MoveComp = PlayerCharacter->GetCharacterMovement())
        {
            bIsFalling = MoveComp->IsFalling();
        }
        else
        {
            bIsFalling = false;
        }
    }
}