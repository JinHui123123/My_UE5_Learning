// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "GameFramework/SpringArmComponent.h" //game framwork用来添加摄像机臂组件的头文件
#include "Camera/CameraComponent.h"

#include "EnhancedInputSubsystems.h" //EnhancedInputSubsystem 是UE5中用于处理输入系统的头文件，包含了输入映射上下文、输入动作等相关类的定义
#include "EnhancedInputComponent.h" //EnhancedInputComponent 是UE5中用于处理输入组件的头文件，包含了输入组件的定义和相关函数的声明
#include "InputActionValue.h" //InputActionValue 是UE5中用于处理输入动作值的头文件，包含了输入动作值的定义和相关函数的声明
#include "GameFramework/PlayerController.h" //PlayerController 是UE5中用于处理玩家控制器的头文件，包含了玩家控制器的定义和相关函数的声明
	


APlayerCharacter::APlayerCharacter() //定义玩家角色的构造函数
{
	//添加摄像机组件
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));

	//将摄像机臂组件附加到根组件上
	CameraBoom->SetupAttachment(RootComponent); //RootComponent是角色的根组件，默认是一个胶囊组件

	//设置摄像机臂组件的长度
	CameraBoom->TargetArmLength = 500.0f;

	//添加摄像机组件
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	//将摄像机组件附加到摄像机臂组件上
	Camera->SetupAttachment(CameraBoom);

	

}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();//调用父类的BeginPlay函数

	//获取玩家控制器
	APlayerController* PlayerController = Cast<APlayerController>(GetController()); //GetController()函数是APawn类中的一个成员函数，用于获取当前角色的控制器。Cast<APlayerController>()函数是UE4中的一个模板函数，用于将一个对象转换为指定类型的指针，如果转换成功则返回该指针，否则返回nullptr。

	//如果玩家控制器存在，则获取输入子系统并添加输入映射上下文
	if(PlayerController)
	{
		//获取输入子系统
		//UEnhancedInputLocalPlayerSubsystem 是UE5中用于处理输入系统的子系统类，提供了添加和移除输入映射上下文等功能。ULocalPlayer::GetSubsystem<T>()函数是UE4中的一个模板函数，用于获取指定类型的子系统实例，如果该子系统不存在则会创建一个新的实例并返回。
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()); // PlayerController->GetLocalPlayer()函数是APlayerController类中的一个成员函数，用于获取当前玩家控制器所属的本地玩家对象。ULocalPlayer是UE4中的一个类，表示一个本地玩家对象，包含了玩家的输入、HUD、网络等相关信息。
		
		//如果输入子系统存在，则添加输入映射上下文
		if (Subsystem)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0); //AddMappingContext()函数是UEnhancedInputLocalPlayerSubsystem类中的一个成员函数，用于添加一个输入映射上下文到输入系统中。DefaultMappingContext是APlayerCharacter类中的一个成员变量，表示默认的输入映射上下文。第二个参数0表示该输入映射上下文的优先级，数值越小优先级越高。
		} 
	}
}
//->是C++中的成员访问运算符，用于访问指针所指向对象的成员函数或成员变量。

void APlayerCharacter::Move(const FInputActionValue & value)
{
	UE_LOG(LogTemp, Display, TEXT("Run Move Function"));
}

void APlayerCharacter::Look(const FInputActionValue& value)
{

}


void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);//调用父类的Tick函数
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) // SetupPlayerInputComponent ()函数是AActor类中的一个虚函数，用于设置角色的输入组件。
{
	//调用父类的SetupPlayerInputComponent函数
	UEnhancedInputComponent* MyInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent); 
	// MyInputComponent是一个指向UEnhancedInputComponent类型的指针，用于存储输入组件的实例。Cast<UEnhancedInputComponent>()函数是UE4中的一个模板函数，用于将一个对象转换为指定类型的指针，如果转换成功则返回该指针，否则返回nullptr。
	if (MyInputComponent)
	{
		MyInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);

		MyInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&APlayerCharacter::Move);
//BindAction()函数是UEnhancedInputComponent类中的一个成员函数，用于绑定一个输入动作到一个函数。MoveAction是APlayerCharacter类中的一个成员变量，表示移动输入动作。ETriggerEvent::Triggered表示当输入动作被触发时调用绑定的函数。this表示当前对象的指针。&APlayerCharacter::Move表示要绑定的函数指针，指向APlayerCharacter类中的Move函数。

	}
}
