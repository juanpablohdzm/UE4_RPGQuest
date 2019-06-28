// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <GameplayAbilities/Public/AbilitySystemInterface.h>
#include "GameFramework/Character.h"
#include "Interfaces/RPGAttributeSetInterface.h"
#include "RPGCharacter.generated.h"

class UAbilitySystemComponent;
class UGameplayAbility;
class URPGAttributeSet;
class AActor;

UCLASS()
class RPGQUEST_API ARPGCharacter : public ACharacter,public IAbilitySystemInterface, public IRPGAttributeSetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARPGCharacter();


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*Get Functions*/
	UFUNCTION(BlueprintCallable, Category = "RPG Character")
		bool GetIsDead() const { return IsDead; }

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "IRPGAttributeSet")
		URPGAttributeSet* GetAttributeSetComp();
		virtual URPGAttributeSet* GetAttributeSetComp_Implementation() override { return AttributeSetComp; }

	/*Functions*/
	UFUNCTION(BlueprintCallable, Category = "AbilitySystem")
		virtual void AquireAbility(const TSubclassOf<UGameplayAbility>& AbilityToAquire);

	UFUNCTION(BlueprintCallable, Category = "AbilitySystem")
		virtual void AquireAbilities(const TArray<TSubclassOf<UGameplayAbility>>& AbilitiesToAquire);

	UFUNCTION(BlueprintCallable, Category = "CharacterAbilities")
		void PushCharacter(AActor* OtherActor=nullptr, float AngleToLaunchActor = 30.0f, float LaunchMagnitude = 2000.0f, bool ShouldIgnoreZ = true);	
	
	UFUNCTION(BlueprintCallable, Category = "RPGCharacter")
		virtual void DisableController();

	UFUNCTION(BlueprintCallable, Category = "RPGCharacter")
		virtual void EnableController();

protected:

	/*Components*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UAbilitySystemComponent* AbilitySystemComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class URPGAttributeSet* AttributeSetComp;	

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

	/*Variables*/
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "RPG Character")
	bool IsDead;
	
};
