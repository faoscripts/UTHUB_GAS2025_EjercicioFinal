#include "Abilities/FireballProjectile.h"

#include "AbilitySystemComponent.h"
#include "UTHUB_ASC.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

AFireballProjectile::AFireballProjectile()
{
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	RootComponent = CollisionComponent;

	CollisionComponent->SetCollisionProfileName(TEXT("Projectile"));
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AFireballProjectile::OnHit);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 1000.f;
	ProjectileMovement->MaxSpeed = 1000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
}

void AFireballProjectile::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Error, TEXT("LA BOLA DE FUEGO SE HA INSTANCIADO"));
}

void AFireballProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (!OtherActor || OtherActor == SourceActor) return;

	if (UUTHUB_ASC* TargetASC = OtherActor->FindComponentByClass<UUTHUB_ASC>())
	{
		for (const auto& EffectClass : DamageEffects)
			{
				if (EffectClass)
				{
					TargetASC->ApplyEffectFromClass(EffectClass);
				}
			}
	}

	if (ExplosionEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorTransform());
	}
	
	Destroy(); // Destruye la bola tras impactar
}
