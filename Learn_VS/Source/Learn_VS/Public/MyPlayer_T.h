// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyPlayer_T.generated.h"

class USpringArmComponent; //摄像机臂组件
class UCameraComponent; //摄像机组件


UCLASS()
class LEARN_VS_API AMyPlayer_T : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayer_T();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//BluePrintCallable 允许在蓝图中调用这个函数
	//BluePrintpure 允许在蓝图中调用这个函数，并且不允许修改任何状态
	//BluePrintImplementableEvent 允许在蓝图中实现这个函数，但是不能在C++中实现
	//Gategory 分类
	//Meta 允许在蓝图中显示这个函数的提示信息
	//Server、Client、NetMulticast 允许在服务器、客户端或者所有人中调用这个函数
	//BluePrintNativeEvent 允许在蓝图中实现这个函数，并且可以在C++中实现，如果在蓝图中实现了这个函数，那么C++中的实现将不会被调用

//public:
//	UFUNCTION(BlueprintPure)
//	bool IsSuccess_T();
//
//	UFUNCTION(BluePrintCallable)
//	void ReducePlayerHealth_T();
//
//	UFUNCTION(BlueprintImplementableEvent)
//	void CustomEvent_T();
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom; //摄像机臂组件

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera; //摄像机组件


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
