// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/AbilityBase_Busy.h"
#include "AbilityAttackBase.generated.h"

UCLASS()
class UTHUB_GAS2025_API UAbilityAttackBase : public UAbilityBase_Busy
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	TArray<TSubclassOf<UGameplayEffect>> DamageEffects;

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;

private:
	UFUNCTION()
	void ApplyDamageEffects(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                        UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep,
	                        const FHitResult& SweepResult);

	UFUNCTION()
	void OnAnimationFinished();
	
	UPROPERTY(EditAnywhere, Category = "Attacks", meta=(AllowPrivateAccess=true))
	UAnimMontage* MontageToPlay;
};
