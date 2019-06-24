// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGAttributeSet.h"
#include <GameplayAbilities/Public/GameplayEffectExtension.h>
#include <GameplayAbilities/Public/GameplayEffect.h>

URPGAttributeSet::URPGAttributeSet()
{
	Health = 100.0f;
	Mana = 100.0f;
}

void URPGAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(URPGAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(URPGAttributeSet, Health)))
	{
		Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(), 0.0f, Health.GetBaseValue()));
		OnHealthChange.Broadcast(Health.GetCurrentValue(), Health.GetBaseValue());
		UE_LOG(LogTemp, Warning, TEXT("Current health: %d Max Health: %d"), Health.GetCurrentValue(), Health.GetBaseValue());

// 		ARPGCharacter* owner = Cast<ARPGCharacter>(GetOwningActor());
// 		if (owner && Health.GetCurrentValue() == Health.GetBaseValue())
// 		{
// 			owner->AddGameplayTag(owner->FullHealthTag);
// 		}
// 		else
// 		{
// 			owner->RemoveGameplayTag(owner->FullHealthTag);
// 
// 		}

	}

	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(URPGAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(URPGAttributeSet, Mana)))
	{
		Mana.SetCurrentValue(FMath::Clamp(Mana.GetCurrentValue(), 0.0f, Mana.GetBaseValue()));
		OnManaChange.Broadcast(Mana.GetCurrentValue(), Mana.GetBaseValue());
	}
}
