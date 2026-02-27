// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);
	Camera->bUsePawnControlRotation = false;

}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	//获取玩家控制器
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	//判断玩家控制器是否有效
	if(PlayerController)
	{
		//获取增强输入子系统
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		//判断增强输入子系统是否有效
		if (Subsystem)
		{
			//添加默认输入映射上下文
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}


}

void AMyPlayer::Move(const FInputActionValue & value)
{
	FVector2D movement = value.Get<FVector2D>();

	// 只有当有实际输入时才处理
	if (movement.SizeSquared() > 0.0f && Controller != nullptr) 
	{
		// 获取向前和向右方向（对应蓝图中的 "获取向前向量" 和 "获取向右向量"）
		//    这里使用控制器的旋转（即相机方向），因为蓝图的目标可能是 Camera
		FRotator ControllerRotation = Controller->GetControlRotation();

		// 获取角色朝前的方向（X轴）和朝右的方向（Y轴）
		FVector forward = FRotationMatrix(ControllerRotation).GetUnitAxis(EAxis::Y);
		FVector right = FRotationMatrix(ControllerRotation).GetUnitAxis(EAxis::X);

		// 添加移动输入：前后（W/S）用 Y 分量，左右（A/D）用 X 分量
		AddMovementInput(forward, movement.X);
		AddMovementInput(right, movement.Y);

		// 输出日志验证所有按键
		UE_LOG(LogTemp, Display, TEXT("Move - X: %f,Y: %f"),movement.X,movement.Y);
	}

}

void AMyPlayer::Look(const FInputActionValue& Value)
{
	FVector2D Look = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// 水平视角旋转（左右）
		AddControllerYawInput(Look.X);
		// 垂直视角旋转（上下）
		AddControllerPitchInput(Look.Y);
	}
	
}


// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//调用父类的SetupPlayerInputComponent函数
	UEnhancedInputComponent* MyInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	// MyInputComponent是一个指向UEnhancedInputComponent类型的指针，用于存储输入组件的实例。Cast<UEnhancedInputComponent>()函数是UE4中的一个模板函数，用于将一个对象转换为指定类型的指针，如果转换成功则返回该指针，否则返回nullptr。
	if (MyInputComponent)
	{
		MyInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyPlayer::Look);

		MyInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AMyPlayer::Jump);
		MyInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMyPlayer::StopJumping);

		MyInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayer::Move);
		//BindAction()函数是UEnhancedInputComponent类中的一个成员函数，用于绑定一个输入动作到一个函数。MoveAction是APlayerCharacter类中的一个成员变量，表示移动输入动作。ETriggerEvent::Triggered表示当输入动作被触发时调用绑定的函数。this表示当前对象的指针。&APlayerCharacter::Move表示要绑定的函数指针，指向APlayerCharacter类中的Move函数。
	}
}
	

