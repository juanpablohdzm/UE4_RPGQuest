// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGCharacter.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <Components/CapsuleComponent.h>
#include <../Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/AbilitySystemComponent.h>
#include <../Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/GameplayAbility.h>
#include <../Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayAbilitySpec.h>
#include "RPGAttributeSet.h"


// Sets default values
ARPGCharacter::ARPGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FinalFOV = 45.0f;
	bWantsToZoom = false;

	AngleToLaunchActor = 30.0f;
	LaunchMagnitude = 2000.0f;

	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(FName("AbilitySystemComp"));
	AttributeSetComp = CreateDefaultSubobject<URPGAttributeSet>(FName("AttributeSet"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->AddRelativeLocation(FVector(0.0f, 0.0f, 65.0f));
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	Camera->SetupAttachment(SpringArm);

	WeaponCapsule = CreateDefaultSubobject<UCapsuleComponent>(FName("WeaponCollider"));
	

}

// Called when the game starts or when spawned
void ARPGCharacter::BeginPlay()
{
	Super::BeginPlay();
	OrginalFOV = Camera->FieldOfView;
}



void ARPGCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (WeaponCapsule)
	{
		FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
		WeaponCapsule->AttachToComponent(GetMesh(), AttachmentTransformRules, FName(TEXT("weapon_r")));
		WeaponCapsule->SetRelativeLocation(FVector(-1.33f, -69.62f, 5.94));
		WeaponCapsule->SetRelativeRotation(FQuat(FRotator(0.0f, 0.0f, 91.21f)));
	}

	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	if (CapsuleComp)
	{
		CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &ARPGCharacter::PushActor);
	}

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

	if (bWantsToZoom)
		Camera->SetFieldOfView(FMath::Lerp(Camera->FieldOfView, FinalFOV, DeltaTime));
	else		
		Camera->SetFieldOfView(FMath::Lerp(Camera->FieldOfView, OrginalFOV, DeltaTime));


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

void ARPGCharacter::OnHealthChange(float Value, float MaxValue)
{
	K2_OnHealthChange(Value, MaxValue);
}

void ARPGCharacter::OnManaChange(float Value, float MaxValue)
{
	K2_OnManaChange(Value, MaxValue);
}

void ARPGCharacter::PushActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		FVector Direction = OtherActor->GetActorLocation();
		Direction.Normalize();

		FVector RightDirectionAxis = FVector::CrossProduct(Direction, FVector::UpVector);
		Direction.RotateAngleAxis(AngleToLaunchActor, RightDirectionAxis);


		ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
		if (OtherCharacter)
		{
			OtherCharacter->LaunchCharacter(Direction * LaunchMagnitude, true, true);
		}
		else
		{
			if (OtherComp->IsSimulatingPhysics())
			{
				OtherComp->AddImpulse(Direction * LaunchMagnitude,NAME_None,true);
			}
		}

	}
}

