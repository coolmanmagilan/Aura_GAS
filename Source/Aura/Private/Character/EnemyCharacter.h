// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "Interaction/EnemyInterface.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AEnemyCharacter : public ABaseCharacter, public IEnemyInterface //IEnemyInterface is a custom class that we created
{
	GENERATED_BODY()
	
public:
	AEnemyCharacter();

	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
};
