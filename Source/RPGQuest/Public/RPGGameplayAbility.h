// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "RPGGameplayAbilityInfo.h"
#include "RPGGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class RPGQUEST_API URPGGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Info")
		class UMaterialInstance* Material;

	UFUNCTION(BlueprintCallable)
		virtual FGameplayAbilityInfo GetAbilityInfo();
};
