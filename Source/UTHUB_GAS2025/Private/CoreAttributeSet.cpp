// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreAttributeSet.h"
#include "UTHUB_GAS2025/UTHUB_GAS2025Character.h"

void UCoreAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		AActor* Owner = GetOwningActor();
		if (AUTHUB_GAS2025Character* Player = Cast<AUTHUB_GAS2025Character>(Owner))
		{
			if (NewValue < Health.GetCurrentValue())
			{
				Player->OnDamageReceived();
			}
		}
	}
}