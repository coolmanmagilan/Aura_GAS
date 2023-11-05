// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "AuraPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	// Called to bind functionality to input

protected:
	

private:
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue);

	
	
};
