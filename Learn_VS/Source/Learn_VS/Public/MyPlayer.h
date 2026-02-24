// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyPlayer.generated.h"

UCLASS()
class LEARN_VS_API AMyPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UPROPERTY宏
	//VisibleAnywhere: 在编辑器中可见，但不可编辑
	//VisibleDefaultsOnly: 在主编辑器中不显示，但在蓝图编辑器中可见且不可编辑
	//EditAnywhere: 在编辑器中可见且可编辑
	//EditDefaultsOnly: 在主编辑器中不可见，但在蓝图编辑器中可见且可编辑
	//EditInstanceOnly: 在主编辑器中不可见，但在蓝图编辑器中可见且可编辑（仅限实例）
	//BlueprintReadOnly: 在蓝图中可读，但不可写
	//Category: 在编辑器中为属性分组
	//Meta: 其他属性，如显示名称、工具提示等    meta=(AllowPrivateAccess = "ture"//允许在蓝图中访问私有成员变量)


//private:
//	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="State|Health",meta=(AllowPrivateAccess = "ture"))
//	float Health;

	//BlueprintCallable: 允许在蓝图中调用该函数
public:
	UFUNCTION(BlueprintCallable)
	void PlayerHealth();



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
