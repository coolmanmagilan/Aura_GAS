// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "AuraCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
/**
 * 
 */
UCLASS()
class AAuraCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:

	AAuraCharacter();

protected:
	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;


private:
	UPROPERTY(EditAnywhere, Category = "Component")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, Category = "Component")
	UCameraComponent* CameraComponent;

	void GetAuraMovement();
	void GetAuraComponent();

	//This is InitAbilityActorInfo in course
	virtual void GetInitAbilityActorInfo() override;

};
