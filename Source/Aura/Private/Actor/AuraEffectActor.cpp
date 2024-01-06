// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AuraEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
//#include "AbilitySystem/AuraAttributeSet.h"
//#include "Components/SphereComponent.h"
//#include "AbilitySystemInterface.h"

AAuraEffectActor::AAuraEffectActor()
{

	//Struct will not update every frame
	PrimaryActorTick.bCanEverTick = false; //if you do not need tick function, then disable tick itself. 

	/*---------------------------------------------------------------------------------------------------
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SetRootComponent(StaticMesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(StaticMesh);
	---------------------------------------------------------------------------------------------------*/

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));

}


//void AAuraEffectActor::BeginPlay()
//{
//	Super::BeginPlay();

	/*---------------------------------------------------------------------------------------------------
	called when something starts to overlaps this component, for example a player walking into a trigger.
	  In this case, a Sphere Mesh overlapping the Actor Class*/
	  //Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnOverlap);
	  //Sphere->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::EndOverlap);
	  /*AddDynamic calls for a dynamic multicast delegate*/
	  //-------------------------------------------------------------------------------------------------- 
//}


void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr) return;

	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);

	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);


	//Apply a gameplay effect to the target ability system component(the target can health, mana, etc.)
	FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	//we dereference the raw pointer of Data

	//Def is the gameplay effect
	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap) {
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
	}
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}

	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap) {
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap){
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}

	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap) {
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}

	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap) {
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}

	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap) {
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

		if (!IsValid(TargetASC)) return;

		TArray<FActiveGameplayEffectHandle> HandleToRemove;
		for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair : ActiveEffectHandles)
		{
			if (TargetASC == HandlePair.Value) {
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
				HandleToRemove.Add(HandlePair.Key);
			}
		}
		for (FActiveGameplayEffectHandle& Handle : HandleToRemove) {
			ActiveEffectHandles.FindAndRemoveChecked(Handle);
		}
	}
	
}





//--------------------------------------------------------------------------------------------------
/*OnOverlap is used as a trigger when the character overlaps with the sphere-like Health Potion(Other Actor)*/
//void AAuraEffectActor::OnOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
//	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){	
	/*---------------------------------------------------------------------------------------------------------------------
		UAuraAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass())
		Our PlayerState is derived from IAbilitySystemInterface, which has a function GetAbilitySystemComponent()
		So what we need to do to manipulate Health in AbilitySystem is Get the AttributeSet from AbilitySystemComponent
		Returns a UAttributeSet, which is why we cast to a UAuraAttributeSet.
		It also returns a const, which is why we define AuraAttributeSet as a const
		*/
	//if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	//{	
	//	const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));


		//TODO: Change this to apply a Gameplay EFFect. For now, using const_cast as a hack
		//We use const_cast because AuraAttributeSet is const meaning we cannot use it to manipulate variable
		//UAuraAttributeSet* MutableAuraAttributeSet = const_cast<UAuraAttributeSet*>(AuraAttributeSet);
	//	MutableAuraAttributeSet->SetHealth(AuraAttributeSet->GetHealth() + 25.F);
	//	MutableAuraAttributeSet->SetMana(AuraAttributeSet->GetMana() - 25.F);
		//---------------------------------------------------------------------------------------------------------------------//

	//	Destroy();
	//}
//}

/*
void AAuraEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}
*/
//--------------------------------------------------------------------------------------------------