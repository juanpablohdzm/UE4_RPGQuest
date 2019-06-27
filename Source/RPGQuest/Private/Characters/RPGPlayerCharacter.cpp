// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGPlayerCharacter.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <Components/CapsuleComponent.h>
#include <GameFramework/Character.h>
#include "RPGPlayerController.h"
#include "RPGGameplayAbility.h"
#include <GameplayAbility.h>

ARPGPlayerCharacter::ARPGPlayerCharacter()
{
	FinalFOV = 45.0f;
	bWantsToZoom = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->AddRelativeLocation(FVector(0.0f, 0.0f, 65.0f));
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	Camera->SetupAttachment(SpringArm);

	WeaponCapsule = CreateDefaultSubobject<UCapsuleComponent>(FName("WeaponCollider"));


}

void ARPGPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	OrginalFOV = Camera->FieldOfView;
}

void ARPGPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bWantsToZoom)
		Camera->SetFieldOfView(FMath::Lerp(Camera->FieldOfView, FinalFOV, DeltaTime));
	else
		Camera->SetFieldOfView(FMath::Lerp(Camera->FieldOfView, OrginalFOV, DeltaTime));

}



void ARPGPlayerCharacter::AquireAbility(const TSubclassOf<UGameplayAbility>& AbilityToAquire)
{
	Super::AquireAbility(AbilityToAquire);

	if (AbilityToAquire->IsChildOf(URPGGameplayAbility::StaticClass()))
	{		
		ARPGPlayerController* PC = Cast<ARPGPlayerController>(GetController());
		if (PC)
		{
			URPGGameplayAbility* AbilityInstance = AbilityToAquire.Get()->GetDefaultObject<URPGGameplayAbility>();
			if (AbilityInstance)
			{
				FGameplayAbilityInfo AbilityInfo = AbilityInstance->GetAbilityInfo();
				PC->SetupUI(AbilityInfo);
			}
		}		
	}
}

void ARPGPlayerCharacter::EnableController()
{
	ARPGPlayerController* PC = Cast<ARPGPlayerController>(GetController());
	if (PC)
	{
		PC->EnableInput(PC);
	}
}

void ARPGPlayerCharacter::DisableController()
{
	ARPGPlayerController* PC = Cast<ARPGPlayerController>(GetController());
	if (PC)
	{
		PC->DisableInput(PC);
	}
}

void ARPGPlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (WeaponCapsule)
	{
		FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
		WeaponCapsule->AttachToComponent(GetMesh(), AttachmentTransformRules, FName(TEXT("weapon_r")));
		WeaponCapsule->SetRelativeLocation(FVector(-1.33f, -69.62f, 5.94));
		WeaponCapsule->SetRelativeRotation(FQuat(FRotator(0.0f, 0.0f, 91.21f)));
	}

}
