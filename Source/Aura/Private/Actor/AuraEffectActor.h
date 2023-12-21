// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class USphereComponent;
class UGameplayEffect;

UCLASS()
class AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAuraEffectActor();

	
	/*TO learn about the paramaters of a function, click on it's defintion. 
	If it does not provide the necessary defintion, then click defintion on it's type*/

	/*
	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlapComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor,					//the other actor that overlapped the sphere component
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex);
	*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GamplayEffectClass);

	UPROPERTY(EditAnywhere, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

private:	
	/*
	//Mesh is a sphere-shape, not a sphere itself. So to simplify the capsule for physical collision, we use a sphere.
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	//Effect Actors ca
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMesh;
	*/

};
