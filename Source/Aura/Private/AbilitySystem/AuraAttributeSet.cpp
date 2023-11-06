// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet()
{

}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,
		Health,										//it's going to replicate Health from UAuraAttributeSet
		COND_None,									//it's going to replicate without any conditions
		REPNOTIFY_Always);							/*if the value is set on the server, replicate it
													 and on the client, that value will be updates on set*/

	/*Note: REPNOTIFY_ONCHANGE will only replicate the variable if the value of health on the server change
			This is optimization. If you're setting it to the same value, then there's no need to replicate it*/	

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,
		MaxHealth,										
		COND_None,									
		REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,
		Mana,										
		COND_None,									
		REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,
		MaxMana,										
		COND_None,									
		REPNOTIFY_Always);
}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	/*updates our 'current value' to the server
	the value will then come back to the client and change if valid
	Note: The ability system will register tha change until it is valid
	If not valid, the server can roll back that change*/
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}
