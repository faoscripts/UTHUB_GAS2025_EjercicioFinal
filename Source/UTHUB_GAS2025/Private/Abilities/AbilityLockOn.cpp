#include "Abilities/AbilityLockOn.h"
#include "GameplayTagAssetInterface.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "UTHUB_GAS2025/UTHUB_GAS2025Character.h"

void UAbilityLockOn::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                     const FGameplayAbilityActorInfo* ActorInfo,
                                     const FGameplayAbilityActivationInfo ActivationInfo,
                                     const FGameplayEventData* TriggerEventData)
{
	ACharacter* Avatar = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
	if (!Avatar) return;

	static AActor* CurrentTarget = nullptr;
	if (CurrentTarget)
	{
		CurrentTarget = nullptr;
		Avatar->bUseControllerRotationYaw = false;
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
	CurrentTarget = FindClosestEnemy();
	if (!CurrentTarget)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	Avatar->bUseControllerRotationYaw = true;
	FTimerDelegate LookAtDelegate;
	LookAtDelegate.BindLambda([Avatar]()
	{
		if (CurrentTarget && Avatar)
		{
			FVector Direction = CurrentTarget->GetActorLocation() - Avatar->GetActorLocation();
			FRotator NewRot = Direction.Rotation();
			NewRot.Pitch = 0.f;
			NewRot.Roll = 0.f;

			Avatar->SetActorRotation(NewRot);
		}
	});
	
	FTimerHandle TimerHandle;
	Avatar->GetWorldTimerManager().SetTimer(
		TimerHandle, LookAtDelegate, 0.01f, true
	);
}

AActor* UAbilityLockOn::FindClosestEnemy() const
{
	ACharacter* Avatar = Cast<ACharacter>(GetAvatarActorFromActorInfo());
	if (!Avatar) return nullptr;

	TArray<AActor*> AllCharacters;
	UGameplayStatics::GetAllActorsOfClass(Avatar->GetWorld(), AUTHUB_GAS2025Character::StaticClass(), AllCharacters);

	AActor* ClosestEnemy = nullptr;
	float ClosestDist = FLT_MAX;
	for (AActor* Actor : AllCharacters)
	{
		AUTHUB_GAS2025Character* PotentialEnemy = Cast<AUTHUB_GAS2025Character>(Actor);
		if (!PotentialEnemy || PotentialEnemy == Avatar) continue;
		if (PotentialEnemy->GetCharacterClassTag().MatchesTag(EnemyTag))
		{
			float Dist = FVector::Dist(PotentialEnemy->GetActorLocation(), Avatar->GetActorLocation());
			if (Dist < ClosestDist)
			{
				ClosestDist = Dist;
				ClosestEnemy = PotentialEnemy;
			}
		}
	}

	return ClosestEnemy;
}

