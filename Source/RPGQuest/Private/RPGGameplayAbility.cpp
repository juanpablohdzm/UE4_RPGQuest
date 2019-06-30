// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameplayAbility.h"
#include <../Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayEffect.h>

FGameplayAbilityInfo URPGGameplayAbility::GetAbilityInfo()
{
	FGameplayAbilityInfo AbilityInfo;

	UGameplayEffect* CoolDownEffect = GetCooldownGameplayEffect();
	UGameplayEffect* CostEffect = GetCostGameplayEffect();

	if (CoolDownEffect)
	{
		//Get cooldown duration
		float CoolDown = 0;
		CoolDownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(1, CoolDown);
		AbilityInfo.CooldownDuration = CoolDown;
	}

	if (CostEffect)
	{
		float Cost = 0;
		if (CostEffect->Modifiers.Num() > 0)
		{
			//Get effect cost
			FGameplayModifierInfo EffectInfo = CostEffect->Modifiers[0];
			EffectInfo.ModifierMagnitude.GetStaticMagnitudeIfPossible(1, Cost);
			AbilityInfo.Cost = Cost;

			//Get effect type
			FGameplayAttribute CostAttr = EffectInfo.Attribute;
			FString AttributeName = CostAttr.AttributeName;
			if (AttributeName == "HEALTH")
			{
				AbilityInfo.CostType = EAbilityCostType::HEALTH;
			}
			else
			{
				if (AttributeName == "MANA")
				{
					AbilityInfo.CostType = EAbilityCostType::MANA;
				}
				else
				{
					if (AttributeName == "STAMINA")
					{
						AbilityInfo.CostType = EAbilityCostType::STAMINA;
					}
					else
					{
						AbilityInfo.CostType = EAbilityCostType::NONE;
					}
				}
			}
		}
	}
	AbilityInfo.Material = Material;
	AbilityInfo.AbilityClass = GetClass();

	return AbilityInfo;
}
