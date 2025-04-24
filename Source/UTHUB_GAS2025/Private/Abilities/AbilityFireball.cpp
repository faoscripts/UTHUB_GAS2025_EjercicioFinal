// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AbilityFireball.h"
#include "Abilities/FireballProjectile.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"

void UAbilityFireball::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                       const FGameplayAbilityActivationInfo ActivationInfo,
                                       const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UAbilityTask_PlayMontageAndWait* PlayMontageAndWait =
		UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, MontageToPlay);

	PlayMontageAndWait->OnCompleted.AddDynamic(this, &ThisClass::OnAnimationFinished);
	
	PlayMontageAndWait->Activate();
	
	AActor* Avatar = GetAvatarActorFromActorInfo();
	if (!Avatar || !FireballClass) return;

	FVector SpawnLocation = Avatar->GetActorLocation() + Avatar->GetActorForwardVector() * 100.f;
	FRotator SpawnRotation = Avatar->GetActorRotation();

	FActorSpawnParameters Params;
	Params.Owner = Avatar;
	Params.Instigator = Cast<APawn>(Avatar);

	AFireballProjectile* Projectile = Avatar->GetWorld()->SpawnActor<AFireballProjectile>(FireballClass, SpawnLocation, SpawnRotation, Params);
	if (Projectile)
	{
		Projectile->SetSource(Avatar);
		Projectile->SetGameplayEffect(DamageEffects);
	}
}

void UAbilityFireball::OnAnimationFinished()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}