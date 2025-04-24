// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AbilityDodge.h"

#include "UTHUB_ASC.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Components/PrimitiveComponent.h"

void UAbilityDodge::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AActor* Avatar = ActorInfo->AvatarActor.Get();
	check(Avatar);

	TArray<UPrimitiveComponent*> Components;
	Avatar->GetComponents(Components);

	for (UPrimitiveComponent* PrimitiveComp : Components)
	{
		PrimitiveComp->SetGenerateOverlapEvents(false);
	}

	UAbilityTask_PlayMontageAndWait* PlayMontageAndWait =
		UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, MontageToPlay);

	PlayMontageAndWait->OnCompleted.AddDynamic(this, &ThisClass::OnAnimationFinished);
	
	PlayMontageAndWait->Activate();
}

void UAbilityDodge::OnAnimationFinished()
{
	TArray<UPrimitiveComponent*> Components;
	GetAvatarActorFromActorInfo()->GetComponents(Components);

	for (UPrimitiveComponent* PrimitiveComp : Components)
	{
		PrimitiveComp->SetGenerateOverlapEvents(true);
	}
	
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}
