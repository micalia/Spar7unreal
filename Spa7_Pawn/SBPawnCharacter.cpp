// Fill out your copyright notice in the Description page of Project Settings.


#include "SBPawnCharacter.h"
#include "SpartaPlayerController.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
ASBPawnCharacter::ASBPawnCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	CapsuleComp->SetupAttachment(RootComponent);
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(CapsuleComp);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = true;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;
	
	SKMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SKMesh"));
	SKMesh->SetupAttachment(CapsuleComp);
}

// Called when the game starts or when spawned
void ASBPawnCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASBPawnCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASBPawnCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		if (ASpartaPlayerController* PC = Cast<ASpartaPlayerController>(GetController())) {
			if (PC->MoveAction) {
				EnhancedInput->BindAction(PC->MoveAction,
				ETriggerEvent::Triggered,
				this,
				&ASBPawnCharacter::Move
				);
			}
			if (PC->JumpAction) {
				EnhancedInput->BindAction(PC->JumpAction,
				ETriggerEvent::Triggered,
				this,
				&ASBPawnCharacter::StartJump
				);

				EnhancedInput->BindAction(PC->JumpAction,
				ETriggerEvent::Completed,
				this,
				&ASBPawnCharacter::StopJump
				);
			}
			if (PC->LookAction) {
				EnhancedInput->BindAction(PC->LookAction,
				ETriggerEvent::Triggered,
				this,
				&ASBPawnCharacter::Look
				);
			}

			if (PC->SprintAction) {
				EnhancedInput->BindAction(PC->SprintAction,
					ETriggerEvent::Triggered,
					this,
					&ASBPawnCharacter::StartSprint
				);

				EnhancedInput->BindAction(PC->SprintAction,
					ETriggerEvent::Completed,
					this,
					&ASBPawnCharacter::StopSprint
				);
			}
		}
	}
}

void ASBPawnCharacter::Move(const FInputActionValue& value)
{
	if(!Controller)return;
	const FVector2D MoveInput = value.Get<FVector2D>();
	
	FVector MoveDir; 

	// 부동소숫점방식은 딱 0으로 떨어지기 쉽지않기 떄문에 값이 0과 유사하다면 0으로 처리
	if (!FMath::IsNearlyZero(MoveInput.X)) {
		MoveDir += GetActorForwardVector() * MoveInput.X;
	}
	if (!FMath::IsNearlyZero(MoveInput.Y)) {
		MoveDir += GetActorRightVector() * MoveInput.Y;
	}

	FVector MoveOffset; 
	if (!MoveDir.IsZero()) {
		MoveDir.Normalize();
		MoveOffset = MoveDir * moveSpeed * UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	}

	//AddActorLocalOffset(MoveOffset, true);
	AddActorWorldOffset(MoveOffset, false);
	//AddMovementInput(GetActorForwardVector(), MoveInput.X);
}

void ASBPawnCharacter::StartJump(const FInputActionValue& value)
{
	if (!Controller)return;
	if (value.Get<bool>()) {
		//Jump();
	}
}

void ASBPawnCharacter::StopJump(const FInputActionValue& value)
{
	if (!Controller)return;
}

void ASBPawnCharacter::Look(const FInputActionValue& value)
{
	if (!Controller)return;
	FVector2D LookInput = value.Get<FVector2D>();
	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}

void ASBPawnCharacter::StartSprint(const FInputActionValue& value)
{
	if (!Controller)return;
}

void ASBPawnCharacter::StopSprint(const FInputActionValue& value)
{
	if (!Controller)return;
}

