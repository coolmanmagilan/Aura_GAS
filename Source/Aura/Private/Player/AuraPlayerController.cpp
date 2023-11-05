// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

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

	check(Subsystem);
	Subsystem->AddMappingContext(InputMappingContext, 0);

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

	//CursorTrace();
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



