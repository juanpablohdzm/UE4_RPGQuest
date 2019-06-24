// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RPGPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RPGQUEST_API ARPGPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	virtual void SetupInputComponent() override; 

	void MoveForward(float value);

	void MoveRight(float value);

};
