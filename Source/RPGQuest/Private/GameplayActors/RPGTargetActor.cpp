// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGTargetActor.h"
#include <Components/DecalComponent.h>
#include <GameplayAbility.h>
#include <GameplayAbilityTargetActor.h>
#include "RPGPlayerController.h"



ARPGTargetActor::ARPGTargetActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Radius = 200.0f;

	RootComp = CreateDefaultSubobject<USceneComponent>(FName("RootComp"));
	SetRootComponent(RootComp);

	DecalComp = CreateDefaultSubobject<UDecalComponent>(FName("DecalComp"));
	DecalComp->DecalSize = FVector(Radius);
	DecalComp->SetupAttachment(RootComponent);

}

void ARPGTargetActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	SetActorLocation(GetTargetLocation());
}

void ARPGTargetActor::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);
	MasterPC = Cast<ARPGPlayerController>(Ability->GetOwningActorFromActorInfo()->GetInstigatorController());
}

void ARPGTargetActor::ConfirmTargetingAndContinue()
{
	TArray<FOverlapResult> OverlapResult;
	TArray<TWeakObjectPtr<AActor>> OverlapedActors;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(MasterPC->GetPawn());

	if (GetWorld()->OverlapMultiByChannel(OverlapResult, GetActorLocation(), 
		FQuat::Identity, ECC_Visibility, 
		FCollisionShape::MakeSphere(Radius), QueryParams))
	{
		for (size_t i = 0; i < OverlapResult.Num(); i++)
		{
			APawn* Pawn = Cast<APawn>(OverlapResult[i].GetActor());
			if (Pawn)
			{
				OverlapedActors.Add(Pawn);
			}
		}
	}

	FGameplayAbilityTargetData_LocationInfo* CenterLocation = new FGameplayAbilityTargetData_LocationInfo();
	CenterLocation->TargetLocation.LiteralTransform = GetActorTransform();
	CenterLocation->TargetLocation.LocationType = EGameplayAbilityTargetingLocationType::LiteralTransform;

	if (OverlapedActors.Num())
	{
		FGameplayAbilityTargetDataHandle TargetData = StartLocation.MakeTargetDataHandleFromActors(OverlapedActors);
		TargetData.Add(CenterLocation);
		TargetDataReadyDelegate.Broadcast(TargetData);
	}
	else
	{
		FGameplayAbilityTargetDataHandle TargetData;
		TargetData.Add(CenterLocation);
		TargetDataReadyDelegate.Broadcast(FGameplayAbilityTargetDataHandle(TargetData));
	}
}

FVector ARPGTargetActor::GetTargetLocation()
{
	FVector OwnerPosition; 
	FRotator OwnerRotation;
	MasterPC->GetPlayerViewPoint(OwnerPosition, OwnerRotation);

	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = true;
	QueryParams.AddIgnoredActor(MasterPC->GetPawn());

	FHitResult HitResult; 
	if (GetWorld()->LineTraceSingleByChannel(HitResult, OwnerPosition, OwnerPosition + OwnerRotation.Vector() * 10000.0f, ECC_Visibility, QueryParams))
	{
		return HitResult.ImpactPoint;
	}

	return FVector::ZeroVector;
}
