// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/RPGGameplayAbility.h"
#include "GA_MeleeBase_CPP.generated.h"

class UAnimMontage;

/**
 * 
 */
UCLASS()
class ACTIONRPG_API UGA_MeleeBase_CPP : public URPGGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility( const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData );

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	UAnimMontage* MontageToPlay = nullptr;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	FGameplayTagContainer EventTags;

private:
	UFUNCTION()
	void EndAbility_( FGameplayTag EventTag, FGameplayEventData EventData );

	// Immediately apply an effect container, it will normally use the event data for targeting
	UFUNCTION()
	void ApplyEffectContainer_( FGameplayTag EventTag, FGameplayEventData EventData );
};
