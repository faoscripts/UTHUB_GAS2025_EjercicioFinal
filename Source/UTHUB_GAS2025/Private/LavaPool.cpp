#include "LavaPool.h"
#include "GameFramework/Character.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "CoreAttributeSet.h"
#include "UTHUB_GAS2025/UTHUB_GAS2025Character.h"
#include "Engine/World.h"
#include "TimerManager.h"

ALavaPool::ALavaPool()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    RootComponent = CollisionBox;
    CollisionBox->SetCollisionProfileName(TEXT("Trigger"));
}

void ALavaPool::BeginPlay()
{
    Super::BeginPlay();
}

void ALavaPool::NotifyActorBeginOverlap(AActor* OtherActor)
{
    if (ACharacter* Player = Cast<ACharacter>(OtherActor))
    {
        UE_LOG(LogTemp, Warning, TEXT("Detectado: %s"), *OtherActor->GetName());
        UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Player);
        if (ASC)
        {
            if (!CharactersInLava.Contains(Player))
            {
                FTimerHandle TimerHandle;
                GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, Player]()
                {
                    ApplyPeriodicDamage(Player);
                }, DamageInterval, true);

                CharactersInLava.Add(Player, TimerHandle);
            }
        }
    }
}

void ALavaPool::NotifyActorEndOverlap(AActor* OtherActor)
{
    if (ACharacter* Player = Cast<ACharacter>(OtherActor))
    {
        if (CharactersInLava.Contains(Player))
        {
            GetWorld()->GetTimerManager().ClearTimer(CharactersInLava[Player]);
            CharactersInLava.Remove(Player);
        }

        UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Player);
        if (ASC && LavaDamageEffect)
        {
            ASC->RemoveActiveGameplayEffectBySourceEffect(LavaDamageEffect, ASC);
            UE_LOG(LogTemp, Warning, TEXT("Efecto de daño eliminado para: %s"), *Player->GetName());
        }
    }
}

void ALavaPool::ApplyPeriodicDamage(ACharacter* Character)
{
    if (!Character)
        return;

    UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Character);
    if (!ASC)
        return;

    if (LavaDamageEffect)
    {
        FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(LavaDamageEffect, 1.0f, ASC->MakeEffectContext());
        if (EffectSpecHandle.IsValid())
        {
            ASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
            UE_LOG(LogTemp, Warning, TEXT("Daño aplicado a: %s"), *Character->GetName());
        }
    }

    // Verificar si la salud del personaje llega a 0
    if (AUTHUB_GAS2025Character* PlayerCharacter = Cast<AUTHUB_GAS2025Character>(Character))
    {
        UCoreAttributeSet* Attributes = PlayerCharacter->GetCoreAttributeSet();
        if (!Attributes)
        {
            UE_LOG(LogTemp, Error, TEXT("Attributes es nullptr en ApplyPeriodicDamage"));
            return;
        }

        if (Attributes->Health.GetCurrentValue() <= 0)
        {
            UE_LOG(LogTemp, Warning, TEXT("EL PERSONAJE ESTÁ MUERTO"));
        }
    }
}

