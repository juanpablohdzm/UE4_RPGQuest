// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGAttributeSet.h"
#include <GameplayAbilities/Public/GameplayEffectExtension.h>
#include <GameplayAbilities/Public/GameplayEffect.h>

URPGAttributeSet::URPGAttributeSet()
{
	MaxHealth = Health = 100.0f;
	MaxMana = Mana = 100.0f;
	Stamina = 0.0f;
	MaxStamina = 100.0f;
}

void URPGAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(URPGAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(URPGAttributeSet, Health)))
	{
		Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(), 0.0f, MaxHealth.GetBaseValue()));
		OnHealthChange.Broadcast(Health.GetCurrentValue(), MaxHealth.GetBaseValue());

	}

	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(URPGAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(URPGAttributeSet, Mana)))
	{
		Mana.SetCurrentValue(FMath::Clamp(Mana.GetCurrentValue(), 0.0f, MaxMana.GetBaseValue()));
		OnManaChange.Broadcast(Mana.GetCurrentValue(), MaxMana.GetBaseValue());
	}

	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(URPGAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(URPGAttributeSet, Stamina)))
	{
		Stamina.SetCurrentValue(FMath::Clamp(Stamina.GetCurrentValue(), 0.0f, MaxStamina.GetBaseValue()));
		OnStaminaChange.Broadcast(Stamina.GetCurrentValue(), MaxStamina.GetBaseValue());
	}
}

void URPGAttributeSet::ChangeHealthAmount(float amount)
{
	Health.SetCurrentValue(amount);
	Health.SetBaseValue(amount);

	MaxHealth.SetCurrentValue(amount);
	MaxHealth.SetBaseValue(amount);
}

void URPGAttributeSet::ChangeManaAmount(float amount)
{
	Mana.SetCurrentValue(amount);
	Mana.SetBaseValue(amount);

	MaxMana.SetCurrentValue(amount);
	MaxMana.SetBaseValue(amount);
}

