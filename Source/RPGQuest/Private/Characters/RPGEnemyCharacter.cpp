// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGEnemyCharacter.h"
#include <Perception/PawnSensingComponent.h>



ARPGEnemyCharacter::ARPGEnemyCharacter()
{
	SightComp = CreateDefaultSubobject<UPawnSensingComponent>(FName("SightSense"));
}

void ARPGEnemyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (SightComp)
	{
		SightComp->OnSeePawn.AddDynamic(this, &ARPGEnemyCharacter::OnPawnSeen);
	}
}

void ARPGEnemyCharacter::OnPawnSeen(APawn* Pawn)
{
	K2_OnPawnSeen(Pawn);
}

