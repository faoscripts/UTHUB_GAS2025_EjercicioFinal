// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/AbilityBase_Busy.h"
#include "AbilityDodge.generated.h"

/**
 * 
 */
UCLASS()
class UTHUB_GAS2025_API UAbilityDodge : public UAbilityBase_Busy
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
								 const FGameplayAbilityActivationInfo ActivationInfo,
								 const FGameplayEventData* TriggerEventData) override;


private:
	UFUNCTION()
	void OnAnimationFinished();
	
	UPROPERTY(EditDefaultsOnly, Category = "Dodge")
	FGameplayTag InvulnerableTag;
	
	UPROPERTY(EditAnywhere, Category = "Dodge", meta=(AllowPrivateAccess=true))
	UAnimMontage* MontageToPlay;
};
