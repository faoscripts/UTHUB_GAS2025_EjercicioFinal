// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AbilityBase_Busy.generated.h"

/**
 * 
 */
UCLASS()
class UTHUB_GAS2025_API UAbilityBase_Busy : public UGameplayAbility
{
	GENERATED_BODY()

public:
	
	UAbilityBase_Busy();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;
};
