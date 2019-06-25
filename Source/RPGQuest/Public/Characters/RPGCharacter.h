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
	UFUNCTION(BlueprintCallable)
	class UCapsuleComponent* GetWeaponCapsule() const { return WeaponCapsule; }

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "IRPGAttributeSet")
		URPGAttributeSet* GetAttributeSetComp() ;
		virtual URPGAttributeSet* GetAttributeSetComp_Implementation() override { return AttributeSetComp; }

	/*Functions*/
	UFUNCTION(BlueprintCallable, Category = "AbilitySystem")
		virtual void AquireAbility(const TSubclassOf<UGameplayAbility>& AbilityToAquire);

	UFUNCTION(BlueprintCallable, Category = "AbilitySystem")
		virtual void AquireAbilities(const TArray<TSubclassOf<UGameplayAbility>>& AbilitiesToAquire);

	/*Variables*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CharacterAbilities")
		bool bWantsToZoom;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CharacterAbilities")
		float AngleToLaunchActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CharacterAbilities")
		float LaunchMagnitude;
	

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

	/*Variables*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CharacterAbilities")
		float FinalFOV;


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

private:

	/*Variables*/
	float OrginalFOV;

	/*Functions*/
	UFUNCTION()
		void PushActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
