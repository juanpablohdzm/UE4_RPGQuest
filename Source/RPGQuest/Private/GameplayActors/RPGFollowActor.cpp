// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGFollowActor.h"
#include <Kismet/GameplayStatics.h>
#include <TimerManager.h>
#include <Components/DecalComponent.h>
#include <GameplayAbility.h>
#include <GameplayAbilityTargetActor.h>
#include <DrawDebugHelpers.h>

ARPGFollowActor::ARPGFollowActor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	Radius = 200.0f;
	LastImpactPoint = FVector::ZeroVector;

	RootComp = CreateDefaultSubobject<USceneComponent>(FName("RootComp"));
	SetRootComponent(RootComp);

	DecalComp = CreateDefaultSubobject<UDecalComponent>(FName("DecalComp"));
	DecalComp->DecalSize = FVector(Radius);
	DecalComp->SetupAttachment(RootComponent);

}

void ARPGFollowActor::BeginPlay()
{
	GetWorldTimerManager().SetTimer(TimerHandle_StartActorLocation,this, &ARPGFollowActor::GetTargetPosition,0.01f,true,0.0f);
	FTimerDelegate StopTimer;
	StopTimer.BindLambda([this]()
		{
			GetWorldTimerManager().ClearTimer(TimerHandle_StartActorLocation);
		});

	GetWorldTimerManager().SetTimer(TimerHandle_EndActorLocation, StopTimer, 5.0f, false);
}

void ARPGFollowActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	SetActorLocation(LastImpactPoint);
}

void ARPGFollowActor::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);
	OwningActor = Ability->GetOwningActorFromActorInfo();
}

void ARPGFollowActor::ConfirmTargetingAndContinue()
{
	TArray<FOverlapResult> OverlapResult;
	TArray<TWeakObjectPtr<AActor>> OverlapedActors;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(OwningActor);

	if (GetWorld()->OverlapMultiByChannel(OverlapResult, GetActorLocation(),
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

void ARPGFollowActor::GetTargetPosition()
{
	APawn* Pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (Pawn)
	{
		LastImpactPoint = Pawn->GetActorLocation()+ LocationOffset;
	}
}



