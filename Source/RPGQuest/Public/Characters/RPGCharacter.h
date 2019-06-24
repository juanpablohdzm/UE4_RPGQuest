// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <GameplayAbilities/Public/AbilitySystemInterface.h>
#include "GameFramework/Character.h"
#include "RPGCharacter.generated.h"

class UAbilitySystemComponent;
class UGameplayAbility;

UCLASS()
class RPGQUEST_API ARPGCharacter : public ACharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARPGCharacter();

	UFUNCTION(BlueprintCallable)
	class UCapsuleComponent* GetWeaponCapsule() const { return WeaponCapsule; }

protected:

	/*Components*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UAbilitySystemComponent* AbilitySystemComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class URPGAttributeSet* AttributeSetComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UCapsuleComponent* WeaponCapsule;


protected:

	/*Functions*/
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override; 

	UFUNCTION()
		void OnHealthChange(float Value, float MaxValue);

	UFUNCTION(BlueprintImplementableEvent, Category = "AttributeDelegatesChange")
		void K2_OnHealthChange(float Value, float MaxValue);

	UFUNCTION()
		void OnManaChange(float Value, float MaxValue);

	UFUNCTION(BlueprintImplementableEvent, Category = "AttributeDelegatesChange")
		void K2_OnManaChange(float Value, float MaxValue);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, Category = "AbilitySystem")
		virtual void AquireAbility(const TSubclassOf<UGameplayAbility>& AbilityToAquire);

	UFUNCTION(BlueprintCallable, Category = "AbilitySystem")
		virtual void AquireAbilities(const TArray<TSubclassOf<UGameplayAbility>>& AbilitiesToAquire);

};
