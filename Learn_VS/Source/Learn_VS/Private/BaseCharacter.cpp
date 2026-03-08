// Fill out your copyright notice in the Description page of Project Settings.

//导入当前类的头文件
#include "BaseCharacter.h"
#include "BaseWeapon.h"

// Sets default values
ABaseCharacter::ABaseCharacter() //定义构造函数，构造函数的名字必须和类名一样
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	EquipWeapon();
	
}

void ABaseCharacter::EquipWeapon()
{
	Weapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass); // 创建武器Actor

	if (Weapon) {
		// 修正：直接创建 FAttachmentTransformRules 实例，而不是指针
		FAttachmentTransformRules attachRules(EAttachmentRule::SnapToTarget, false);
		Weapon->AttachToComponent(GetMesh(), attachRules, FName("WeaponPoint"));

		Weapon->SetOwner(this);
	}

}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

