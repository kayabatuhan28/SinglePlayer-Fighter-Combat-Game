// Fill out your copyright notice in the Description page of Project Settings.


#include "MageAnim.h"

#include "Kismet/GameplayStatics.h"

void UMageAnim::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	playerRef = Cast<AFighterCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
}

void UMageAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	MageRef = Cast<AMageCharacter>(TryGetPawnOwner());
}

void UMageAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(MageRef)
	{
		Speed = TryGetPawnOwner()->GetVelocity().Size();
		Direction = CalculateDirection(TryGetPawnOwner()->GetVelocity(),TryGetPawnOwner()->GetActorRotation());
	}
}

void UMageAnim::CastPrimaryAttack()
{
	FVector SpawnLoc = MageRef->GetMesh()->GetSocketLocation("hand_l");
	FRotator SpawnRot = MageRef->GetActorRotation();
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
	AActor* SpawnlananAc =	GetWorld()->SpawnActor<AActor>(SkillsActor[0],SpawnLoc,SpawnRot,Params);
}

void UMageAnim::CastBackDashAndPrimaryAttack()
{
	FVector SpawnLoc = MageRef->GetMesh()->GetSocketLocation("Staff_Root");
	FRotator SpawnRot = MageRef->GetActorRotation();
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
	AActor* SpawnlananAc =	GetWorld()->SpawnActor<AActor>(SkillsActor[1],SpawnLoc,SpawnRot,Params);
}

void UMageAnim::CastGroundSmash()
{
	FVector SpawnLoc = MageRef->GetMesh()->GetSocketLocation("Staff_Root");
	FRotator SpawnRot = MageRef->GetActorRotation();
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
	AActor* SpawnlananAc =	GetWorld()->SpawnActor<AActor>(SkillsActor[2],SpawnLoc,SpawnRot,Params);
}

void UMageAnim::CastFrostArea()
{
	if(playerRef)
	{
		FVector SpawnLoc = playerRef->GetActorLocation();
		FRotator SpawnRot = FRotator(FRotator::ZeroRotator);
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
		AActor* SpawnlananAc =	GetWorld()->SpawnActor<AActor>(SkillsActor[3],SpawnLoc,SpawnRot,Params);
	}
}

void UMageAnim::CastFlyGroundSmash()
{
	FVector SpawnLoc = MageRef->GetMesh()->GetSocketLocation("Staff_Root");
	FRotator SpawnRot = MageRef->GetActorRotation();
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
	AActor* SpawnlananAc =	GetWorld()->SpawnActor<AActor>(SkillsActor[4],SpawnLoc,SpawnRot,Params);
}

void UMageAnim::CastHeavyProjectile()
{
	FVector SpawnLoc = MageRef->GetMesh()->GetSocketLocation("hand_r");
	FRotator SpawnRot = MageRef->GetActorRotation();
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
	AActor* SpawnlananAc =	GetWorld()->SpawnActor<AActor>(SkillsActor[5],SpawnLoc,SpawnRot,Params);
}

void UMageAnim::CastFly4SmallProjectile()
{
	FVector SpawnLoc = MageRef->GetMesh()->GetSocketLocation("hand_r");
	FRotator SpawnRot = MageRef->GetActorRotation();
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
	AActor* SpawnlananAc =	GetWorld()->SpawnActor<AActor>(SkillsActor[6],SpawnLoc,SpawnRot,Params);
}

void UMageAnim::CastFly4BigProjectile()
{
	FVector SpawnLoc = MageRef->GetMesh()->GetSocketLocation("hand_r");
	FRotator SpawnRot = MageRef->GetActorRotation();
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
	AActor* SpawnlananAc =	GetWorld()->SpawnActor<AActor>(SkillsActor[7],SpawnLoc,SpawnRot,Params);
}
