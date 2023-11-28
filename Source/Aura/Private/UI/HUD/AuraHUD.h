// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class APlayerController;
class APlayerState;
class UAttributeSet;
class UAbilitySystemComponent;
class UAuraUserWidget;
class UOverlayAuraWidgetController;
struct FWidgetControllerParams;
/**
 * 
 */
UCLASS()
class AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;

	UOverlayAuraWidgetController* GetOverlayWidgetController(const FWidgetControllerParams WCparams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
	
protected:

	
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayAuraWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayAuraWidgetController> OverlayWidgetControllerClass;
};
