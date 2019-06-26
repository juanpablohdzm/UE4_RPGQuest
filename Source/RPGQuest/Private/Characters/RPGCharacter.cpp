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

void ARPGCharacter::PushCharacter(AActor* OtherActor, float AngleToLaunchActor /*= 30.0f*/, float LaunchMagnitude /*= 2000.0f*/)
{
	if (OtherActor && OtherActor != this)
	{
		FVector Direction = OtherActor->GetActorLocation() - GetActorLocation();
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

void ARPGCharacter::OnHealthChange(float Value, float MaxValue)
{
	K2_OnHealthChange(Value, MaxValue);
}

void ARPGCharacter::OnManaChange(float Value, float MaxValue)
{
	K2_OnManaChange(Value, MaxValue);
}


