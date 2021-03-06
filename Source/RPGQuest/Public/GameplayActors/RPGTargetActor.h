// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "RPGTargetActor.generated.h"

/**
 * 
 */
UCLASS()
class RPGQUEST_API ARPGTargetActor : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

protected:
	virtual FVector GetTargetPosition();

	FVector LastImpactPoint;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameplayAbility Actor")
		class USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameplayAbility Actor")
		class UDecalComponent* DecalComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GameplayAbility Actor")
		float Radius;


public:
	ARPGTargetActor();

	void Tick(float DeltaSeconds) override; 

	virtual void StartTargeting(UGameplayAbility* Ability) override;
	virtual void ConfirmTargetingAndContinue() override; 
	
};
