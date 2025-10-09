// Fill out your copyright notice in the Description page of Project Settings.


#include "CloseCombatAnim.h"

void UCloseCombatAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	EnemyRef = Cast<ACloseCombatCharacter>(TryGetPawnOwner());
}

void UCloseCombatAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(EnemyRef)
	{
		Speed = TryGetPawnOwner()->GetVelocity().Size();
		Direction = CalculateDirection(TryGetPawnOwner()->GetVelocity(),TryGetPawnOwner()->GetActorRotation());
	}
}

void UCloseCombatAnim::CastBasicRightKick()
{
	FVector SpawnLoc = EnemyRef->GetMesh()->GetSocketLocation("foot_r");
	FRotator SpawnRot = EnemyRef->GetActorRotation();
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
	AActor* SpawnlananAc =	GetWorld()->SpawnActor<AActor>(SkillsActor[0],SpawnLoc,SpawnRot,Params);
}

void UCloseCombatAnim::CastBasicRightPunch()
{
	FVector SpawnLoc = EnemyRef->GetMesh()->GetSocketLocation("hand_r");
	FRotator SpawnRot = EnemyRef->GetActorRotation();
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
	AActor* SpawnlananAc =	GetWorld()->SpawnActor<AActor>(SkillsActor[1],SpawnLoc,SpawnRot,Params);
}
