// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayAuraWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayAuraWidgetController::BroadcastInitialValues()
{
	//no need to use Super: since this function in AuraWidgetControlller is empty

	//recall that OverlayAuraWidgetController is a child of AuraWidgetController, which has the variable AttributeSet
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	//DON'T FORGET POINTERS!!! YOU ARE CONVERTING POINTER TO POINTER. NOT POINTER TO VARIABLE
	//IF YOU CAN, TRY TO ASSIGN VARIABLE AND INSTANT TO CONST BY DEFAULT


	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
}
