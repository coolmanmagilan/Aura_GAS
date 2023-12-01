// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayAuraWidgetController.generated.h"


/*We create dynamic multicast delegates because
1. we want to assign events to them in Widget Blueprint(WBP)  ---dynamic
2. multiple widget blueprints may want to bind to the delegate so that they can update
*/

/*
We specifically choose OneParams for DECLARE_DYNAMIC_MULTICAST_DELEGATE because
we want to pass a value through the delegate

Below, we declare a delegate that can broadcast a float
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);

/*We put a "signiture" at the end to specify that this a delegate type.
FOnHealthChangedSigniture is delegate binded to NewHealth.

Note, we can check all common delegate Macro such as DECLARE_DYNAMIC_MULTICAST_DELEGATE 
	  in DelegateCombination.h(included with core minimal)
*/

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthMaxSignature, float, MaxHealth);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class UOverlayAuraWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;

	/*It should be noted that FOnHealthChangedSignature is the delegate type 
	  but OnHealthChanged is the delegate*/
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHealthMaxSignature OnMaxHealthChanged;

private:
	
};
