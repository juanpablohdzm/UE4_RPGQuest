// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGPlayerController.h"
#include <Kismet/GameplayStatics.h>
#include <Camera/PlayerCameraManager.h>
#include "RPGCharacter.h"

void ARPGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("LookUp",this, &ARPGPlayerController::AddPitchInput);
	InputComponent->BindAxis("Rotate",this, &ARPGPlayerController::AddYawInput);
	InputComponent->BindAxis("MoveForward",this, &ARPGPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight",this, &ARPGPlayerController::MoveRight);

	InputComponent->BindAction("Jump",EInputEvent::IE_Pressed,this, &ARPGPlayerController::Jump);
}

void ARPGPlayerController::MoveForward(float value)
{
	APawn* pawn = GetPawn();
	APlayerCameraManager* camera = UGameplayStatics::GetPlayerCameraManager(GetWorld(),0);
	if (pawn)
	{
		if(camera)
			pawn->AddMovementInput(camera->GetActorForwardVector() * value);
		else
			pawn->AddMovementInput(pawn->GetActorForwardVector() * value);

	}
}

void ARPGPlayerController::MoveRight(float value)
{
	APawn* pawn = GetPawn();
	APlayerCameraManager* camera = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	if (pawn)
	{
		if (camera)
			pawn->AddMovementInput(camera->GetActorRightVector() * value);
		else
			pawn->AddMovementInput(pawn->GetActorRightVector() * value);

	}
}

void ARPGPlayerController::Jump()
{
	ARPGCharacter* character = Cast<ARPGCharacter>(GetPawn());
	if (character)
	{
		character->Jump();
	}
}
