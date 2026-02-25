// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

APlayerCharacter::APlayerCharacter()
{
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();//调用父类的BeginPlay函数
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);//调用父类的Tick函数
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

}
