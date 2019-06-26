// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Materials/MaterialInstance.h>
#include "RPGGameplayAbilityInfo.generated.h"


class URPGGameplayAbility;
/**
 * 
 */
UENUM(BlueprintType)
enum class EAbilityCostType : uint8
{
	HEALTH, MANA, NONE
};

USTRUCT(BlueprintType)
struct FGameplayAbilityInfo
{
	GENERATED_BODY()

public:
	FGameplayAbilityInfo();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
		UMaterialInstance* Material;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
		float CooldownDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
		float Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
		EAbilityCostType CostType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
		TSubclassOf<URPGGameplayAbility> AbilityClass;


};
