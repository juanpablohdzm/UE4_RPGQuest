// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayActors/RPGTargetActor.h"
#include "RPGFollowActor.generated.h"

/**
 * 
 */
UCLASS()
class RPGQUEST_API ARPGFollowActor :public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

private:
	FTimerHandle TimerHandle_StartActorLocation;
	FTimerHandle TimerHandle_EndActorLocation;

	AActor* OwningActor;

protected:

	virtual void BeginPlay() override; 

	void GetTargetPosition();

	FVector LastImpactPoint;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameplayAbility Actor")
		class USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameplayAbility Actor")
		class UDecalComponent* DecalComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GameplayAbility Actor")
		float Radius;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GameplayAbility Actor")
		FVector LocationOffset;


public:
	ARPGFollowActor();

	void Tick(float DeltaSeconds) override;

	virtual void StartTargeting(UGameplayAbility* Ability) override;
	virtual void ConfirmTargetingAndContinue() override;

	
};
