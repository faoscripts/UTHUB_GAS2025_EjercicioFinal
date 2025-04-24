// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/AbilityBase_Busy.h"
#include "AbilityFireball.generated.h"

class AFireballProjectile;

UCLASS()
class UTHUB_GAS2025_API UAbilityFireball : public UAbilityBase_Busy
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	TArray<TSubclassOf<UGameplayEffect>> DamageEffects;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	TSubclassOf<AFireballProjectile> FireballClass;
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
								 const FGameplayAbilityActivationInfo ActivationInfo,
								 const FGameplayEventData* TriggerEventData) override;

private:
	UFUNCTION()
	void OnAnimationFinished();
	
	UPROPERTY(EditAnywhere, Category = "Attacks", meta=(AllowPrivateAccess=true))
	UAnimMontage* MontageToPlay;
};
