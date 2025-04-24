// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AbilityDefense.h"

#include "UTHUB_ASC.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAbilityDefense::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                      const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AActor* Avatar = ActorInfo->AvatarActor.Get();
	check(Avatar);

	UUTHUB_ASC* ASC = Avatar->FindComponentByClass<UUTHUB_ASC>();
	
	if(ASC)
	{
		ASC->AddLooseGameplayTag(InvulnerableTag);
	}

	UAbilityTask_PlayMontageAndWait* PlayMontageAndWait =
		UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, MontageToPlay);

	PlayMontageAndWait->OnCompleted.AddDynamic(this, &ThisClass::OnAnimationFinished);

	MovementComponent = Avatar->FindComponentByClass<UCharacterMovementComponent>();
	if(MovementComponent)
	{
		MovementComponent->DisableMovement();
		PlayMontageAndWait->Activate();
	}
}

void UAbilityDefense::OnAnimationFinished()
{
	if (UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo())
	{
		if (InvulnerableTag.IsValid())
		{
			ASC->RemoveLooseGameplayTag(InvulnerableTag);
		}
	}

	MovementComponent->SetMovementMode(MOVE_Walking);
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}