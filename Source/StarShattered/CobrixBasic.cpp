// Fill out your copyright notice in the Description page of Project Settings.


#include "CobrixBasic.h"

// Sets default values
ACobrixBasic::ACobrixBasic()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACobrixBasic::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACobrixBasic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACobrixBasic::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

