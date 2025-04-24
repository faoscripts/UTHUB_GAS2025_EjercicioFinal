#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffect.h"
#include "Components/BoxComponent.h"
#include "LavaPool.generated.h"

UCLASS()
class UTHUB_GAS2025_API ALavaPool : public AActor
{
	GENERATED_BODY()

public:
	ALavaPool();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "LavaPool")
	UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, Category = "LavaPool")
	TSubclassOf<UGameplayEffect> LavaDamageEffect;

	UPROPERTY(EditAnywhere, Category = "LavaPool")
	float DamageInterval = 1.0f; // Intervalo de daño en segundos

	UPROPERTY(EditAnywhere, Category = "LavaPool")
	float DamageAmount = -5.0f; // Cantidad de daño aplicada

	// Mapa para almacenar los personajes que están dentro de la lava
	TMap<ACharacter*, FTimerHandle> CharactersInLava;

	UFUNCTION()
	void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UFUNCTION()
	void NotifyActorEndOverlap(AActor* OtherActor) override;

	void ApplyPeriodicDamage(ACharacter* Character);
};