// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AbilityBase_Busy.h"

UAbilityBase_Busy::UAbilityBase_Busy()
{
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Character.IsBusy")));
	ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Character.IsBusy")));
}

void UAbilityBase_Busy::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                        const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	
}
