// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGPlayerCharacter.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <Components/CapsuleComponent.h>
#include <GameFramework/Character.h>

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
