// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(InputMappingContext);

	//Local Player Subsystem allows us to use mapping context
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	
	//we don't need to assert check since we only need our local controller
	if (Subsystem) {
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
	//Show Mouse cursor when game begins
	bShowMouseCursor = true;

	//Customize Mouse Cursor
	DefaultMouseCursor = EMouseCursor::Default;

	//Allows us to use input from keyboard and mouse to effect User Interface such as widgets
	FInputModeGameAndUI InputMode;

	//We will not lock mouse to viewport and mouse will not be hiddin
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);

	//Regester configuration to game
	SetInputMode(InputMode);

	
}


void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();


	//Cast InputComponent to the Enhanced System
	//CastChecked is similar casting with an 'if' statement
	UEnhancedInputComponent* EnhancedInput = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
		
}


void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	/*
	Transform Rotation into a 3 by 3 Matrix which represents your dpad.
	GetUnitAxis gets a direction from your dpad.
	*/
	const FVector FowardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	//we need to map these control to the pawn controlled by player controller
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		//y is associated with the 'W' and 'S' keys on our controller
		ControlledPawn->AddMovementInput(FowardDirection, InputAxisVector.Y);

		//x is associated with the 'A' and 'D' keys on our controller
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;

	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, CursorHit);

	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor; //update enemy your highlight
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor()); //anything hit touch become 'thisactor'

	/*
	-Line trace from cursor. There are several scenarios
	-A. if LastActor is null && ThisActor is null(wall or floor or something that is not an enemy), then do nothing
	-B. if LastActor is null && ThisActor is valid(ThisActor is an enemy), call Highlight of ThisActor
	-C. if LasterActor is valid && ThisActor is null(unhighlight LastActor)
	-D. if both actors are valid, but LastActor != ThisActor, then switch Highlight from LastActor to ThisActor
	-E. if both actors are valid, but LastActor == ThisActor(we are hovering over the same actor), do nothing
	*/

	if (LastActor == nullptr) {
		if (ThisActor != nullptr) {
			ThisActor->HighlightActor();	 //case B
		//	UE_LOG(LogTemp, Display, TEXT("CASE B"));
		}
		else {
		//	UE_LOG(LogTemp, Display, TEXT("CASE A"));							//case A
		}
	}
	else { //LastActor != nullptr(is valid)
		if (ThisActor == nullptr) {
			LastActor->UnHighlightActor();	//case C
		//	UE_LOG(LogTemp, Display, TEXT("CASE C"));
		}
		else {
			if (LastActor != ThisActor) {
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();  //case D
			//	UE_LOG(LogTemp, Display, TEXT("CASE D"));
			}
			else {
			//	UE_LOG(LogTemp, Display, TEXT("CASE E")); //case E
			}
		}
	}
}