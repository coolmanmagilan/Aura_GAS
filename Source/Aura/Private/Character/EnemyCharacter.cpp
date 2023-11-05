// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyCharacter.h"

AEnemyCharacter::AEnemyCharacter()
{
    GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
}

void AEnemyCharacter::HighlightActor()
{
	/*
	DrawDebugSphere(GetWorld(),
		GetActorLocation(),
		50,
		12,
		FColor::Red,
		false,
		5);
	*/

	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(Stencil);

	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(Stencil);
}	

void AEnemyCharacter::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}
