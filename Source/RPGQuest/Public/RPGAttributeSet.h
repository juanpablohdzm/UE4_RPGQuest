// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "RPGAttributeSet.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttributeChangeDelegate, float, Value, float, MaxValue);
/**
 * 
 */
UCLASS()
class RPGQUEST_API URPGAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	URPGAttributeSet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase")
		FGameplayAttributeData Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase")
		FGameplayAttributeData Mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase")
		FGameplayAttributeData Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase")
		FGameplayAttributeData MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase")
		FGameplayAttributeData MaxMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase")
		FGameplayAttributeData MaxStamina;

	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	FOnAttributeChangeDelegate OnHealthChange;
	FOnAttributeChangeDelegate OnManaChange;
	FOnAttributeChangeDelegate OnStaminaChange;

	UFUNCTION(BlueprintCallable, Category = "AttributeSetBase")
	void ChangeHealthAmount(float amount);

	UFUNCTION(BlueprintCallable, Category = "AttributeSetBase")
	void ChangeManaAmount(float amount);
	
};
