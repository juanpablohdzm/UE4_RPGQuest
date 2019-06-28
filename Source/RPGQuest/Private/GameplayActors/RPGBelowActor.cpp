// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGBelowActor.h"
#include <Components/SceneComponent.h>
#include <Components/DecalComponent.h>
#include "RPGAIController.h"
#include <GameplayAbility.h>



ARPGBelowActor::ARPGBelowActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Radius = 500.0f;

	RootComp = CreateDefaultSubobject<USceneComponent>(FName("RootComp"));
	SetRootComponent(RootComp);

	DecalComp = CreateDefaultSubobject<UDecalComponent>(FName("DecalComp"));
	DecalComp->DecalSize = FVector(Radius);
	DecalComp->SetupAttachment(RootComponent);
}


void ARPGBelowActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	SetActorLocation(OwningActor->GetActorLocation());
}

void ARPGBelowActor::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);
	OwningActor = Ability->GetOwningActorFromActorInfo();
}

void ARPGBelowActor::ConfirmTargetingAndContinue()
{

	TArray<FOverlapResult> OverlapResult;
	TArray<TWeakObjectPtr<AActor>> OverlapedActors;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(OwningActor);

	if (GetWorld()->OverlapMultiByChannel(OverlapResult, GetActorLocation()+Offset,
		FQuat::Identity, ECC_Pawn,
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


