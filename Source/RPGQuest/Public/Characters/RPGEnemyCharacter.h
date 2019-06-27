// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/RPGCharacter.h"
#include "RPGEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class RPGQUEST_API ARPGEnemyCharacter : public ARPGCharacter
{
	GENERATED_BODY()

public:
	ARPGEnemyCharacter();

	virtual void PostInitializeComponents() override; 

	virtual void DisableController() override;

	virtual void EnableController() override; 

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EnemyBehavior")
		class UPawnSensingComponent* SightComp;


	UFUNCTION()
		void OnPawnSeen(APawn* Pawn);

	UFUNCTION(BlueprintImplementableEvent, Category = "EnemyBehavior")
		void K2_OnPawnSeen(APawn* Pawn);
	
};
