// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimCpp.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

void UPlayerAnimCpp::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	playerRef = Cast<AFighterCharacter>(TryGetPawnOwner());
	
}

void UPlayerAnimCpp::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if(playerRef)
	{
		Speed = TryGetPawnOwner()->GetVelocity().Size();
		Direction = CalculateDirection(TryGetPawnOwner()->GetVelocity(),TryGetPawnOwner()->GetActorRotation());
		IsInAir = TryGetPawnOwner()->GetMovementComponent()->IsFalling();
		EquippedWeapon = playerRef->WeaponEquipped;
	}
}

void UPlayerAnimCpp::AttackStart()
{
	playerRef->IsAttacking = true;
}

void UPlayerAnimCpp::AttackEnd()
{
	playerRef->IsAttacking = false;
}

void UPlayerAnimCpp::FlyOn()
{
	playerRef->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
}

void UPlayerAnimCpp::FlyOff()
{
	playerRef->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void UPlayerAnimCpp::CameraZoomOut()
{
	playerRef->GetCameraBoom()->TargetArmLength = 800.f;
}

void UPlayerAnimCpp::CameraZoomIn()
{
	playerRef->GetCameraBoom()->TargetArmLength = 600.f;
}

void UPlayerAnimCpp::CastLeftBasicPunch()
{
	FVector SpawnLoc = playerRef->GetMesh()->GetSocketLocation("hand_l");
	FRotator SpawnRot = playerRef->GetActorRotation();
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
	AActor* SpawnlananAc =	GetWorld()->SpawnActor<AActor>(SkillsActor[0],SpawnLoc,SpawnRot,Params);
}

void UPlayerAnimCpp::CastRightBasicPunch()
{
	FVector SpawnLoc = playerRef->GetMesh()->GetSocketLocation("hand_r");
	FRotator SpawnRot = playerRef->GetActorRotation();
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
	AActor* SpawnlananAc =	GetWorld()->SpawnActor<AActor>(SkillsActor[1],SpawnLoc,SpawnRot,Params);
}

void UPlayerAnimCpp::CastUpperCutPunch()
{
	FVector SpawnLoc = playerRef->GetMesh()->GetSocketLocation("hand_r");
	FRotator SpawnRot = playerRef->GetActorRotation();
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
	AActor* SpawnlananAc =	GetWorld()->SpawnActor<AActor>(SkillsActor[2],SpawnLoc,SpawnRot,Params);
}

void UPlayerAnimCpp::CastKnockdownUpperCut()
{
	FVector SpawnLoc = playerRef->GetMesh()->GetSocketLocation("hand_r");
	FRotator SpawnRot = playerRef->GetActorRotation();
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
	AActor* SpawnlananAc =	GetWorld()->SpawnActor<AActor>(SkillsActor[3],SpawnLoc,SpawnRot,Params);
}

void UPlayerAnimCpp::CastGroundSmash()
{
	FVector SpawnLoc = playerRef->GetMesh()->GetSocketLocation("hand_r");
	FRotator SpawnRot = playerRef->GetActorRotation();
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
	AActor* SpawnlananAc =	GetWorld()->SpawnActor<AActor>(SkillsActor[4],SpawnLoc,SpawnRot,Params);
}

void UPlayerAnimCpp::CastAduket()
{
	FVector SpawnLoc = playerRef->GetMesh()->GetSocketLocation("hand_r");
	FRotator SpawnRot = playerRef->GetActorRotation();
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
	AActor* SpawnlananAc =	GetWorld()->SpawnActor<AActor>(SkillsActor[5],SpawnLoc,SpawnRot,Params);
}

void UPlayerAnimCpp::CastComboBasicPunchRight()
{
	FVector SpawnLoc = playerRef->GetMesh()->GetSocketLocation("hand_r");
	FRotator SpawnRot = playerRef->GetActorRotation();
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
	AActor* SpawnlananAc =	GetWorld()->SpawnActor<AActor>(SkillsActor[6],SpawnLoc,SpawnRot,Params);
}

void UPlayerAnimCpp::CastComboBasicPunchLeft()
{
	FVector SpawnLoc = playerRef->GetMesh()->GetSocketLocation("hand_l");
	FRotator SpawnRot = playerRef->GetActorRotation();
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
	AActor* SpawnlananAc =	GetWorld()->SpawnActor<AActor>(SkillsActor[7],SpawnLoc,SpawnRot,Params);
}

void UPlayerAnimCpp::CastComboFinalPunch()
{
	FVector SpawnLoc = playerRef->GetMesh()->GetSocketLocation("hand_r");
	FRotator SpawnRot = playerRef->GetActorRotation();
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
	AActor* SpawnlananAc =	GetWorld()->SpawnActor<AActor>(SkillsActor[8],SpawnLoc,SpawnRot,Params);
}

void UPlayerAnimCpp::CastSliderSkill()
{
	FVector SpawnLoc = playerRef->GetMesh()->GetSocketLocation("spine_01");
	FRotator SpawnRot = playerRef->GetActorRotation();
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
	AActor* SpawnlananAc =	GetWorld()->SpawnActor<AActor>(SkillsActor[9],SpawnLoc,SpawnRot,Params);
	SpawnlananAc->AttachToComponent(playerRef->GetMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale,"spine_01");
}

void UPlayerAnimCpp::CastHeavyGroundSmash()
{
	FVector SpawnLoc = playerRef->GetMesh()->GetSocketLocation("hand_r");
	FRotator SpawnRot = playerRef->GetActorRotation();
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
	AActor* SpawnlananAc =	GetWorld()->SpawnActor<AActor>(SkillsActor[10],SpawnLoc,SpawnRot,Params);
}

void UPlayerAnimCpp::CastRunKick()
{
	FVector SpawnLoc = playerRef->GetMesh()->GetSocketLocation("foot_l");
	FRotator SpawnRot = playerRef->GetActorRotation();
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
	AActor* SpawnlananAc =	GetWorld()->SpawnActor<AActor>(SkillsActor[11],SpawnLoc,SpawnRot,Params);
}

void UPlayerAnimCpp::CastSpinningKick()
{
	FVector SpawnLoc = playerRef->GetMesh()->GetSocketLocation("spine_01");
	FRotator SpawnRot = playerRef->GetActorRotation();
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
	AActor* SpawnlananAc =	GetWorld()->SpawnActor<AActor>(SkillsActor[12],SpawnLoc,SpawnRot,Params);
	SpawnlananAc->AttachToComponent(playerRef->GetMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale,"spine_01");
}

void UPlayerAnimCpp::CastSummon1()
{
	FVector SpawnLoc =  playerRef->GetMesh()->GetSocketLocation("spine_01");
	FRotator SpawnRot = playerRef->GetActorRotation();
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
	AActor* SpawnlananAc =	GetWorld()->SpawnActor<AActor>(SkillsActor[13],SpawnLoc,SpawnRot,Params);
	
}

void UPlayerAnimCpp::CastSummon2()
{
	FVector SpawnLoc = playerRef->GetMesh()->GetSocketLocation("spine_01");
	FRotator SpawnRot = playerRef->GetActorRotation();
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
	AActor* SpawnlananAc =	GetWorld()->SpawnActor<AActor>(SkillsActor[14],SpawnLoc,SpawnRot,Params);
	
}

void UPlayerAnimCpp::CastSummon3()
{
	FVector SpawnLoc = playerRef->GetMesh()->GetSocketLocation("spine_01");
	FRotator SpawnRot = playerRef->GetActorRotation();
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
	AActor* SpawnlananAc =	GetWorld()->SpawnActor<AActor>(SkillsActor[15],SpawnLoc,SpawnRot,Params);
	
}
