// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "FireballProjectile.generated.h"

class USphereComponent;
class UGameplayEffect;

UCLASS()
class UTHUB_GAS2025_API AFireballProjectile : public AActor
{
	GENERATED_BODY()

public:
	AFireballProjectile();

	UPROPERTY(VisibleAnywhere)
	USphereComponent* CollisionComponent;
	
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	TArray<TSubclassOf<UGameplayEffect>> DamageEffects;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* ExplosionEffect;
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
			   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
			   bool bFromSweep, const FHitResult& Hit);

	UPROPERTY()
	AActor* SourceActor;

public:
	void SetSource(AActor* InSource) { SourceActor = InSource; }
	void SetGameplayEffect(TArray<TSubclassOf<UGameplayEffect>> InEffects) { DamageEffects = InEffects; }
};
