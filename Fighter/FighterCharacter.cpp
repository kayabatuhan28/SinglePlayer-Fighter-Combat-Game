// Copyright Epic Games, Inc. All Rights Reserved.

#include "FighterCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Enemy/MageCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

//////////////////////////////////////////////////////////////////////////
// AFighterCharacter

AFighterCharacter::AFighterCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rate for input
	TurnRateGamepad = 50.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 600.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	
}

void AFighterCharacter::BeginPlay()
{

	Super::BeginPlay();
}

void AFighterCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if(IsSprint == true && CurrentStamina > 0)
	{
		CurrentStamina -= 0.1f;
		if(CurrentStamina <= 0 )
		{
			IsSprint = false;
			SprintEnd();
		}
	}
	else if(IsSprint == false && CurrentStamina < MaxStamina)
	{
		CurrentStamina += 0.1f;
	}
}



//////////////////////////////////////////////////////////////////////////
// Input

void AFighterCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AFighterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AFighterCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &AFighterCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &AFighterCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AFighterCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AFighterCharacter::TouchStopped);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AFighterCharacter::SprintStart);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AFighterCharacter::SprintEnd);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AFighterCharacter::SprintStart);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AFighterCharacter::SprintEnd);
	PlayerInputComponent->BindAction("SlowWalk", IE_Pressed, this, &AFighterCharacter::SlowWalkSet);
	PlayerInputComponent->BindAction("SlowWalk", IE_Released, this, &AFighterCharacter::SlowWalkUnSet);

	PlayerInputComponent->BindAction("EquipWeapon", IE_Pressed, this, &AFighterCharacter::EquippedWeapon);

	PlayerInputComponent->BindAction("LeftMouseAttack", IE_Pressed, this, &AFighterCharacter::LeftBasicPunch);
	PlayerInputComponent->BindAction("RightMouseAttack", IE_Pressed, this, &AFighterCharacter::UpperCut);
	PlayerInputComponent->BindAction("SihftLeftMouseAttack", IE_Pressed, this, &AFighterCharacter::KnockdownUpperCut);
	PlayerInputComponent->BindAction("ShiftRightMouseAttack", IE_Pressed, this, &AFighterCharacter::GroundSmash);
	PlayerInputComponent->BindAction("FlyGroundSmash", IE_Pressed, this, &AFighterCharacter::FlyGroundSmash);
	PlayerInputComponent->BindAction("AduketSkill", IE_Pressed, this, &AFighterCharacter::AduketSkill);
	PlayerInputComponent->BindAction("ComboPunchLifeRegen", IE_Pressed, this, &AFighterCharacter::ComboPunchLifeRegeneration);
	PlayerInputComponent->BindAction("SlideSkill", IE_Pressed, this, &AFighterCharacter::SliderSkill);
	PlayerInputComponent->BindAction("HeavyGroundSmash", IE_Pressed, this, &AFighterCharacter::HeavyGroundSmashSkill);
	PlayerInputComponent->BindAction("RunKick", IE_Pressed, this, &AFighterCharacter::RunKick);
	PlayerInputComponent->BindAction("SpinKick", IE_Pressed, this, &AFighterCharacter::SpinningKick);
	PlayerInputComponent->BindAction("SummonFighter", IE_Pressed, this, &AFighterCharacter::SummonSpirit);

	
	PlayerInputComponent->BindAction("WPressed", IE_Pressed, this, &AFighterCharacter::IsWPressed);
	PlayerInputComponent->BindAction("SPressed", IE_Pressed, this, &AFighterCharacter::IsSPressed);
	PlayerInputComponent->BindAction("APressed", IE_Pressed, this, &AFighterCharacter::IsAPressed);
	PlayerInputComponent->BindAction("DPressed", IE_Pressed, this, &AFighterCharacter::IsDPressed);
	PlayerInputComponent->BindAction("WPressed", IE_Released, this, &AFighterCharacter::IsUnWPressed);
	PlayerInputComponent->BindAction("SPressed", IE_Released, this, &AFighterCharacter::IsUnSPressed);
	PlayerInputComponent->BindAction("APressed", IE_Released, this, &AFighterCharacter::IsUnAPressed);
	PlayerInputComponent->BindAction("DPressed", IE_Released, this, &AFighterCharacter::IsUnDPressed);
	PlayerInputComponent->BindAction("Evade", IE_Pressed, this, &AFighterCharacter::Evade);
}




void AFighterCharacter::SprintStart()
{
	if(WeaponEquipped == true)
	{
		GetCharacterMovement()->MaxWalkSpeed = 900.f;
		IsSprint = true;
	}
	else if(WeaponEquipped == false)
	{
		GetCharacterMovement()->MaxWalkSpeed = 1200.f;
		IsSprint = true;
	}
}

void AFighterCharacter::SprintEnd()
{
	if(WeaponEquipped == true)
	{
		GetCharacterMovement()->MaxWalkSpeed = 450.f;
		IsSprint = false;
	}
	else if(WeaponEquipped == false)
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.f;
		IsSprint = false;
	}
}

void AFighterCharacter::EquippedWeapon()
{
	if(WeaponEquipped == false)
	{
		WeaponEquipped = true;
		M_EquipWeapon->RateScale = 0.8f;
		PlayAnimMontage(M_EquipWeapon);
		GetCharacterMovement()->JumpZVelocity = 700.f;
		GetCharacterMovement()->MaxWalkSpeed = 450.f;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
	}
	else
	{
		WeaponEquipped = false;
		M_UnEquipWeapon->RateScale = 0.8f;
		PlayAnimMontage(M_UnEquipWeapon);
		GetCharacterMovement()->JumpZVelocity = 1000.f;
		GetCharacterMovement()->MaxWalkSpeed = 600.f;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
	}
}

void AFighterCharacter::SlowWalkSet()
{
	if(WeaponEquipped == false)
	{
		GetCharacterMovement()->MaxWalkSpeed = 300.f;
	}
}

void AFighterCharacter::SlowWalkUnSet()
{
	if(WeaponEquipped == false)
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.f;
	}
}


void AFighterCharacter::LeftBasicPunch()
{
	if(CurrentStamina >= 15.f)
	{
		
		if(WeaponEquipped == true && IsAttacking == false && AttackCount == 0)
		{
			PlayAnimMontage(M_Attack[0]);
			CurrentStamina -= 15.f;
			AttackCount++;
		}
		else if(WeaponEquipped == true && IsAttacking == false && AttackCount == 1)
		{
			PlayAnimMontage(M_Attack[1]);
			CurrentStamina -= 15.f;
			AttackCount--;
		}
	}
}

void AFighterCharacter::UpperCut()
{
	if(CurrentStamina >= 25.f )
	{
		if(WeaponEquipped == true && IsAttacking == false && UpperCutCount == 0)
		{
			PlayAnimMontage(M_Attack[2]);
			CurrentStamina -= 25.f;
			UpperCutCount++;
		}
		else if(WeaponEquipped == true && IsAttacking == false && UpperCutCount == 1)
		{
			PlayAnimMontage(M_Attack[3]);
			CurrentStamina -= 25.f;
			UpperCutCount--;
		}
	}
}

void AFighterCharacter::KnockdownUpperCut()
{
	if(CurrentStamina >= 50.f && WeaponEquipped == true && IsAttacking == false )
	{
		PlayAnimMontage(M_Attack[4]);
		CurrentStamina -= 50.f;
	}
}

void AFighterCharacter::GroundSmash()
{
	if(CurrentStamina >= 60.f && WeaponEquipped == true && IsAttacking == false )
	{
		PlayAnimMontage(M_Attack[5]);
		CurrentStamina -= 75.f;
	}
}

void AFighterCharacter::FlyGroundSmash()
{
	if(CurrentStamina >= 70.f && WeaponEquipped == true && IsAttacking == false )
	{
		PlayAnimMontage(M_Attack[6]);
		CurrentStamina -= 70.f;
	}
}

void AFighterCharacter::AduketSkill()
{
	if(CurrentStamina >= 80.f && WeaponEquipped == true && IsAttacking == false )
	{
		PlayAnimMontage(M_Attack[7]);
		CurrentStamina -= 80.f;
	}
}

void AFighterCharacter::ComboPunchLifeRegeneration()
{
	if(CurrentStamina >= 110.f && WeaponEquipped == true && IsAttacking == false )
	{
		PlayAnimMontage(M_Attack[8]);
		CurrentStamina -= 110.f;
	}
}

void AFighterCharacter::SliderSkill()
{
	if(CurrentStamina >= 80.f && WeaponEquipped == true && IsAttacking == false )
	{
		M_Attack[9]->RateScale = 0.8f;
		PlayAnimMontage(M_Attack[9]);
		CurrentStamina -= 80.f;
	}
}

void AFighterCharacter::HeavyGroundSmashSkill()
{
	if(CurrentStamina >= 100.f && WeaponEquipped == true && IsAttacking == false )
	{
		M_Attack[10]->RateScale = 1.f;
		PlayAnimMontage(M_Attack[10]);
		CurrentStamina -= 100.f;
	}
}

void AFighterCharacter::RunKick()
{
	if(CurrentStamina >= 40.f && WeaponEquipped == true && IsAttacking == false )
	{
		M_Attack[11]->RateScale = 0.8f;
		PlayAnimMontage(M_Attack[11]);
		CurrentStamina -= 40.f;
	}
}

void AFighterCharacter::SpinningKick()
{
	if(CurrentStamina >= 70.f && WeaponEquipped == true && IsAttacking == false )
	{
		M_Attack[12]->RateScale = 0.8f;
		PlayAnimMontage(M_Attack[12]);
		CurrentStamina -= 70.f;
	}
}

void AFighterCharacter::SummonSpirit()
{
	if(CurrentStamina >= 135.f && WeaponEquipped == true && IsAttacking == false )
	{
		M_Attack[13]->RateScale = 1.f;
		PlayAnimMontage(M_Attack[13]);
		CurrentStamina -= 135.f;
	}
}


void AFighterCharacter::IsWPressed()
{
	WPressed = true;
}

void AFighterCharacter::IsSPressed()
{
	SPressed = true;
}

void AFighterCharacter::IsAPressed()
{
	APressed = true;
}

void AFighterCharacter::IsDPressed()
{
	DPressed = true;
}

void AFighterCharacter::IsUnWPressed()
{
	WPressed = false;
}

void AFighterCharacter::IsUnSPressed()
{
	SPressed = false;
}

void AFighterCharacter::IsUnAPressed()
{
	APressed = false;
}

void AFighterCharacter::IsUnDPressed()
{
	DPressed = false;
}

void AFighterCharacter::Evade()
{
	if(CurrentStamina >= 20 && WeaponEquipped == true && IsAttacking == false)
	{
		CurrentStamina -= 20;
		if(WPressed == true)
		{
			
			PlayAnimMontage(M_Evade[0]); // W Evade
		}
		else if(SPressed == true)
		{
			
			PlayAnimMontage(M_Evade[1]); // S Evade
		}
		else if(APressed == true)
		{
			
			PlayAnimMontage(M_Evade[2]); // A Evade
		}
		else if(DPressed == true)
		{
			
			PlayAnimMontage(M_Evade[3]); // D Evade
		}
		else
		{
			
			PlayAnimMontage(M_Evade[1]); // S Evade
		}
	}
}

void AFighterCharacter::getBasicHitNoAnim(float Damage, float ReAttackTimer)
{
	if(CurrentHealth - Damage <= 0 && ısDead == false)
	{
		ısDead = true;
		CurrentHealth = 0;
		PlayAnimMontage(M_Die);
	}
	else if(CurrentHealth - Damage >= 0 && ısDead == false)
	{
		IsAttacking = true;
		GetWorld()->GetTimerManager().SetTimer(PlayerAttackTimer,this,&AFighterCharacter::SetIsAttackingAfterHit,ReAttackTimer,false);
		CurrentHealth -= Damage;
	}
}

void AFighterCharacter::getBasicHit(float Damage, float ReAttackTimer)
{
	if(CurrentHealth - Damage <= 0 && ısDead == false)
	{
		ısDead = true;
		CurrentHealth = 0;
		PlayAnimMontage(M_Die);
	}
	else if(CurrentHealth - Damage >= 0 && ısDead == false)
	{
		IsAttacking = true;
		GetWorld()->GetTimerManager().SetTimer(PlayerAttackTimer,this,&AFighterCharacter::SetIsAttackingAfterHit,ReAttackTimer,false);
		PlayAnimMontage(M_Hit[FMath::RandRange(0,1)]);
		CurrentHealth -= Damage;
	}
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void AFighterCharacter::getKnockBackHit(float Damage, float ReAttackTimer)
{
	if(CurrentHealth - Damage <= 0 && ısDead == false)
	{
		ısDead = true;
		CurrentHealth = 0;
		PlayAnimMontage(M_Die);
	}
	else if(CurrentHealth - Damage >= 0 && ısDead == false)
	{
		IsAttacking = true;
		GetWorld()->GetTimerManager().SetTimer(PlayerAttackTimer,this,&AFighterCharacter::SetIsAttackingAfterHit,ReAttackTimer,false);
		PlayAnimMontage(M_Hit[3]);
		CurrentHealth -= Damage;
	}
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void AFighterCharacter::getKnockDownHit(float Damage, float ReAttackTimer)
{
	if(CurrentHealth - Damage <= 0 && ısDead == false)
	{
		ısDead = true;
		CurrentHealth = 0;
		PlayAnimMontage(M_Die);
	}
	else if(CurrentHealth - Damage >= 0 && ısDead == false)
	{
		IsAttacking = true;
		GetWorld()->GetTimerManager().SetTimer(PlayerAttackTimer,this,&AFighterCharacter::SetIsAttackingAfterHit,ReAttackTimer,false);
		PlayAnimMontage(M_Hit[4]);
		CurrentHealth -= Damage;
	}
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void AFighterCharacter::IceAreaIn()
{
	GetWorld()->GetTimerManager().SetTimer(SetIceAreaHitTimer,this,&AFighterCharacter::getIceAreaHit,0.1f,true);
}

void AFighterCharacter::getIceAreaHit()
{
	if(CurrentHealth-2 <= 0 && ısDead == false)
	{
		ısDead = true;
		CurrentHealth = 0;
		PlayAnimMontage(M_Die);
	}
	else if(CurrentHealth-2 >= 0 && ısDead == false)
	{
		IsAttacking = true;
		CurrentHealth -= 2;
	}
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),U_ParticleVfx[0],GetMesh()->GetSocketLocation("spine_01"),FRotator::ZeroRotator,FVector(2.f));
}

void AFighterCharacter::CleargetIceAreaHit()
{
	GetWorld()->GetTimerManager().ClearTimer(SetIceAreaHitTimer);
	IsAttacking = false;
}


void AFighterCharacter::SetIsAttackingAfterHit()
{
	IsAttacking = false;
}

void AFighterCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AFighterCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}



void AFighterCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AFighterCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AFighterCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AFighterCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
