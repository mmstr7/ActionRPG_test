// Copyright Epic Games, Inc. All Rights Reserved.


#include "Abilities/GA_MeleeBase_CPP.h"
#include "Abilities/RPGAbilityTask_PlayMontageAndWaitForEvent.h"

void UGA_MeleeBase_CPP::ActivateAbility( const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData )
{
	Super::ActivateAbility( Handle, ActorInfo, ActivationInfo, TriggerEventData );

	// Handles any costs or cooldowns
	if( CommitAbility( CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo ) == false )
		return;

	// Wait for triggering event
	URPGAbilityTask_PlayMontageAndWaitForEvent* MontageTask = URPGAbilityTask_PlayMontageAndWaitForEvent::PlayMontageAndWaitForEvent(
																this, FName( "None" ), MontageToPlay, EventTags, 1.0f, NAME_None, true, 1.0f );

	MontageTask->OnCompleted.AddDynamic( this, &UGA_MeleeBase_CPP::EndAbility_ );
	MontageTask->OnInterrupted.AddDynamic( this, &UGA_MeleeBase_CPP::EndAbility_ );
	MontageTask->OnCancelled.AddDynamic( this, &UGA_MeleeBase_CPP::EndAbility_ );
	MontageTask->EventReceived.AddDynamic( this, &UGA_MeleeBase_CPP::ApplyEffectContainer_ );

	MontageTask->ReadyForActivation();
}

void UGA_MeleeBase_CPP::EndAbility_( FGameplayTag EventTag, FGameplayEventData EventData )
{
	EndAbility( CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, true );
}

void UGA_MeleeBase_CPP::ApplyEffectContainer_( FGameplayTag EventTag, FGameplayEventData EventData )
{
	ApplyEffectContainer( EventTag, EventData, -1 );
}
