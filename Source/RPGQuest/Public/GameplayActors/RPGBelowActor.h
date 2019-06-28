// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "RPGBelowActor.generated.h"

/**
 * 
 */
UCLASS()
class RPGQUEST_API ARPGBelowActor : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

private:
	AActor* OwningActor;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameplayAbility Actor")
		class USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameplayAbility Actor")
		class UDecalComponent* DecalComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GameplayAbility Actor")
		float Radius;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GameplayAbility Actor")
		FVector Offset;


public:
	ARPGBelowActor();

	virtual void Tick(float DeltaSeconds) override;

	virtual void StartTargeting(UGameplayAbility* Ability) override;
	virtual void ConfirmTargetingAndContinue() override;
	
};
