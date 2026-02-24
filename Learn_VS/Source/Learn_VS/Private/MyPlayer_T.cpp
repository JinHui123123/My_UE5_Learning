// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer_T.h"
#include "GameFramework/SpringArmComponent.h" //摄像机臂组件
#include "Camera/CameraComponent.h" //摄像机组件

// Sets default values
AMyPlayer_T::AMyPlayer_T()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//创建摄像机臂组件,并且将它附加到根组件上
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom_THB"));
	CameraBoom->SetupAttachment(RootComponent);//摄像机臂组件附加到根组件上
	CameraBoom->TargetArmLength = 300.0f;//摄像机臂组件的长度
	CameraBoom->bUsePawnControlRotation = true;//摄像机臂组件使用控制旋转
	CameraBoom->SetRelativeLocation(FVector(-30.0f, -20.0f, -50.0f));//摄像机臂组件的相对位置


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera_XXJ"));
	Camera->SetupAttachment(CameraBoom);//摄像机组件附加到摄像机臂组件上
}

// Called when the game starts or when spawned
void AMyPlayer_T::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPlayer_T::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPlayer_T::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//void AMyPlayer_T::ReducePlayerHealth_T()
//{
//	UE_LOG(LogTemp, Warning, TEXT("Hello World!"));
//
//}
//
//bool AMyPlayer_T::IsSuccess_T()
//{
//	return true;
//}



