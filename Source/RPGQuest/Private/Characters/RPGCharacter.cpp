// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGCharacter.h"
#include <../Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/AbilitySystemComponent.h>
#include <../Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/GameplayAbility.h>
#include <../Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayAbilitySpec.h>
#include "RPGAttributeSet.h"


// Sets default values
ARPGCharacter::ARPGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;	

	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(FName("AbilitySystemComp"));
	AttributeSetComp = CreateDefaultSubobject<URPGAttributeSet>(FName("AttributeSet"));

	IsDead = false;



}

// Called when the game starts or when spawned
void ARPGCharacter::BeginPlay()
{
	Super::BeginPlay();

}



void ARPGCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (AttributeSetComp)
	{
		AttributeSetComp->OnHealthChange.AddDynamic(this, &ARPGCharacter::OnHealthChange);
		AttributeSetComp->OnManaChange.AddDynamic(this, &ARPGCharacter::OnManaChange);
		AttributeSetComp->OnStaminaChange.AddDynamic(this, &ARPGCharacter::OnStaminaChange);
	}
}

// Called every frame
void ARPGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

// Called to bind functionality to input
void ARPGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* ARPGCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

void ARPGCharacter::AquireAbility(const TSubclassOf<UGameplayAbility>& AbilityToAquire)
{
	if (AbilitySystemComp)
	{
		if (HasAuthority() && AbilityToAquire)
		{
			AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(AbilityToAquire, 1, 0));
		}
		AbilitySystemComp->InitAbilityActorInfo(this, this);
	}
}

void ARPGCharacter::AquireAbilities(const TArray<TSubclassOf<UGameplayAbility>>& AbilitiesToAquire)
{
	for (const TSubclassOf<UGameplayAbility>& AbilityItem : AbilitiesToAquire)
	{
		AquireAbility(AbilityItem);		
	}
}

void ARPGCharacter::PushCharacter(AActor* OtherActor, float AngleToLaunchActor /*= 30.0f*/, float LaunchMagnitude /*= 2000.0f*/, bool ShouldIgnoreZ /*= true*/)
{
	if (OtherActor && OtherActor != this)
	{
		FVector Direction;
		if (ShouldIgnoreZ)
		{
			FVector OtherActorLocation = OtherActor->GetActorLocation();
			OtherActorLocation.Z = 0.0f;
			FVector CurrentActorLocation = GetActorLocation();
			CurrentActorLocation.Z = 0.0f;

			Direction = OtherActorLocation - CurrentActorLocation;
		}
		else
		{
			Direction = OtherActor->GetActorLocation() - GetActorLocation();
		}
		Direction.Normalize();

		FVector RightDirectionAxis = FVector::CrossProduct(Direction, FVector::UpVector);
		Direction = Direction.RotateAngleAxis(AngleToLaunchActor, RightDirectionAxis);


		ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
		if (OtherCharacter)
		{
			OtherCharacter->LaunchCharacter(Direction * LaunchMagnitude, true, true);
		}
	}
}

void ARPGCharacter::DisableController()
{

}

void ARPGCharacter::EnableController()
{

}

void ARPGCharacter::OnHealthChange(float Value, float MaxValue)
{
	if (Value <= 0 && !IsDead)
	{
		IsDead = true;
		K2_OnHealthChange(Value, MaxValue);
		DetachFromControllerPendingDestroy();
	}
	if (!IsDead)
	{
		K2_OnHealthChange(Value, MaxValue);
	}
}

void ARPGCharacter::OnManaChange(float Value, float MaxValue)
{
	K2_OnManaChange(Value, MaxValue);
}

void ARPGCharacter::OnStaminaChange(float Value, float MaxValue)
{
	K2_OnStaminaChange(Value, MaxValue);
}

