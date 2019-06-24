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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UAbilitySystemComponent* AbilitySystemComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UCameraComponent* Camera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class USpringArmComponent* SpringArm;

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
