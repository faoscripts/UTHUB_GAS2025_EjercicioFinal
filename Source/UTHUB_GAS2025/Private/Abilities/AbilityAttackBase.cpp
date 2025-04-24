// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AbilityAttackBase.h"

#include "UTHUB_ASC.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameplayCombatUtils/DamageCollisionEvaluator.h"

void UAbilityAttackBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AActor* Avatar = ActorInfo->AvatarActor.Get();
	check(Avatar);

	UDamageCollisionEvaluator* CollisionEvaluator = Avatar->FindComponentByClass<UDamageCollisionEvaluator>();
	if(CollisionEvaluator)
	{
		CollisionEvaluator->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::ApplyDamageEffects);
	}

	UAbilityTask_PlayMontageAndWait* PlayMontageAndWait =
		UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, MontageToPlay);

	PlayMontageAndWait->OnCompleted.AddDynamic(this, &ThisClass::OnAnimationFinished);
	
	PlayMontageAndWait->Activate();
}

void UAbilityAttackBase::ApplyDamageEffects(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == GetAvatarActorFromActorInfo())
		return;

	if (UUTHUB_ASC* TargetASC = OtherActor->FindComponentByClass<UUTHUB_ASC>())
	{
		for (const auto& EffectClass : DamageEffects)
		{
			if (EffectClass)
			{
				TargetASC->ApplyEffectFromClass(EffectClass);
			}
		}
	}
}

void UAbilityAttackBase::OnAnimationFinished()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}
