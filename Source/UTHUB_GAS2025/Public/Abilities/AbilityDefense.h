// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/AbilityBase_Busy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilityDefense.generated.h"

/**
 * 
 */
UCLASS()
class UTHUB_GAS2025_API UAbilityDefense : public UAbilityBase_Busy
{
	GENERATED_BODY()
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
								 const FGameplayAbilityActivationInfo ActivationInfo,
								 const FGameplayEventData* TriggerEventData) override;


private:
	UFUNCTION()
	void OnAnimationFinished();
	
	UPROPERTY(EditDefaultsOnly, Category = "Shield")
	FGameplayTag InvulnerableTag;
	
	UPROPERTY(EditAnywhere, Category = "Shield", meta=(AllowPrivateAccess=true))
	UAnimMontage* MontageToPlay;

	UCharacterMovementComponent* MovementComponent;
};
