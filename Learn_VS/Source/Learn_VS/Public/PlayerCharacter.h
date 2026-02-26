// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent; //声明摄像机臂组件
class UCameraComponent;//声明摄像机组件

//UInputMappingContext用来定义输入映射上下文，它包含了一组输入动作和它们的绑定关系，可以在游戏中动态添加或移除输入映射上下文，以实现不同的输入配置。
class UInputMappingContext; 

//UInputAction用来定义输入动作，它表示玩家可以执行的某个操作，例如移动、跳跃、攻击等。每个输入动作可以绑定一个或多个输入事件，例如按键、鼠标点击、手柄按钮等。当玩家触发这些输入事件时，输入动作会被执行，从而实现相应的游戏功能。
class UInputAction; 

//FInputActionValue用来定义输入动作的值，它表示玩家在执行输入动作时所提供的输入数据，例如按键的状态、鼠标的位置、手柄的摇杆方向等。每个输入动作可以有一个或多个输入值，这些输入值可以在游戏中被读取和处理，以实现不同的游戏功能。
struct FInputActionValue;  //struct是C++中的一个关键字，用于定义一个结构体类型。结构体是一种用户定义的数据类型，可以包含多个成员变量，这些成员变量可以是不同类型的数据。结构体通常用于表示一些相关的数据集合，例如一个玩家角色的属性、一个游戏物体的位置和旋转等。在UE4中，FInputActionValue是一个结构体类型，用于表示输入动作的值，包含了输入数据的相关信息，例如按键的状态、鼠标的位置、手柄的摇杆方向等。
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


		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		USpringArmComponent* CameraBoom;//摄像机臂组件

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		UCameraComponent* Camera; //摄像机组件

		//用于定义持有相关模块成员

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyInput")
		UInputMappingContext* DefaultMappingContext; //输入映射上下文

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyInput")
		UInputAction* MoveAction; //移动输入动作

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyInput")
		UInputAction* LookAction; //查看输入动作

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyInput")
		UInputAction* JumpAction; //跳跃输入动作

		void Move(const FInputActionValue& Value); //移动函数
		void Look(const FInputActionValue& Value); //查看函数

	public:
		virtual void Tick(float DeltaTime) override;

		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
