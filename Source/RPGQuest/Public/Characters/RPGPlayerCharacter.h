// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/RPGCharacter.h"
#include "RPGPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class RPGQUEST_API ARPGPlayerCharacter : public ARPGCharacter
{
	GENERATED_BODY()

public:
	ARPGPlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void AquireAbility(const TSubclassOf<class UGameplayAbility>& AbilityToAquire) override;

	UFUNCTION(BlueprintCallable)
		class UCapsuleComponent* GetWeaponCapsule() const { return WeaponCapsule; }

	/*Variables*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CharacterAbilities")
		bool bWantsToZoom;


protected:
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

private:
	/*Variables*/
	float OrginalFOV;

	/*Functions*/
};
