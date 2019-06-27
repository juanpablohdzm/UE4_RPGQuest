// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGEnemyCharacter.h"
#include <Perception/PawnSensingComponent.h>
#include "RPGAIController.h"
#include <BrainComponent.h>



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

void ARPGEnemyCharacter::DisableController()
{
	ARPGAIController* AIC = Cast<ARPGAIController>(GetController());
	if (AIC)
	{
		AIC->GetBrainComponent()->StopLogic("Stop");
	}

}

void ARPGEnemyCharacter::EnableController()
{
	ARPGAIController* AIC = Cast<ARPGAIController>(GetController());
	if (AIC)
	{
		AIC->GetBrainComponent()->RestartLogic();
	}
}

void ARPGEnemyCharacter::OnPawnSeen(APawn* Pawn)
{
	K2_OnPawnSeen(Pawn);
}

