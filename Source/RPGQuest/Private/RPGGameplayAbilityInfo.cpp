// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameplayAbilityInfo.h"
#include "RPGGameplayAbility.h"

FGameplayAbilityInfo::FGameplayAbilityInfo()
{
	CooldownDuration = 0.0f;
	Cost = 0.0f;
	CostType = EAbilityCostType::NONE;
	AbilityClass = nullptr;
}
