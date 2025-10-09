// Fill out your copyright notice in the Description page of Project Settings.


#include "MageCharacter.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AMageCharacter::AMageCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMageCharacter::getBasicHitNoAnim(float Damage)
{
	if(CurrentHealth - Damage <= 0 && IsDead == false)
	{
		IsDead = true;
		CurrentHealth = 0;
	}
	else
	{
		CurrentHealth -= Damage;
	}
}

void AMageCharacter::getBasicHit(float Damage)
{
	if(CurrentHealth - Damage <= 0 && IsDead == false)
	{
		IsDead = true;
		CurrentHealth = 0;
	}
	else
	{
		CurrentHealth -= Damage;
		PlayAnimMontage(M_BasicHit[FMath::RandRange(0,1)]);
	}
}

void AMageCharacter::getKnockBackHit(float Damage)
{
	if(CurrentHealth - Damage <= 0 && IsDead == false)
	{
		IsDead = true;
		CurrentHealth = 0;
	}
	else
	{
		CurrentHealth -= Damage;
		PlayAnimMontage(M_BasicHit[2]);
	}
}

void AMageCharacter::getKnockDownHit(float Damage)
{
	if(CurrentHealth - Damage <= 0 && IsDead == false)
	{
		IsDead = true;
		CurrentHealth = 0;
	}
	else
	{
		CurrentHealth -= Damage;
		PlayAnimMontage(M_BasicHit[3]);
	}
}

// Called when the game starts or when spawned
void AMageCharacter::BeginPlay()
{
	Super::BeginPlay();
	playerRef = Cast<AFighterCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
}

// Called every frame
void AMageCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMageCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMageCharacter::Attacks()
{
	if(randomAttackCounter == 0) // PrimaryProjectile
	{
		M_Attack[0]->RateScale = AttackSpeed;
		PlayAnimMontage(M_Attack[0]);
	}
	else if(randomAttackCounter == 1) // Strafe
	{
		Strafe(FMath::RandRange(0,2)); 
	}
	else if(randomAttackCounter == 2) 
	{
		M_Attack[1]->RateScale = AttackSpeed;
		PlayAnimMontage(M_Attack[1]);
	}
	else if(randomAttackCounter == 3) 
	{
		M_Attack[2]->RateScale = AttackSpeed;
		PlayAnimMontage(M_Attack[2]);
	}
	else if(randomAttackCounter == 4) 
	{
		M_Attack[3]->RateScale = AttackSpeed;
		PlayAnimMontage(M_Attack[3]);
	}
	else if(randomAttackCounter == 5) 
	{
		M_Attack[4]->RateScale = AttackSpeed;
		PlayAnimMontage(M_Attack[4]);
	}
	else if(randomAttackCounter == 6) 
	{
		M_Attack[5]->RateScale = AttackSpeed;
		PlayAnimMontage(M_Attack[5]);
	}
	else if(randomAttackCounter == 7) 
	{
		M_Attack[6]->RateScale = AttackSpeed;
		PlayAnimMontage(M_Attack[6]);
	}
}

void AMageCharacter::Strafe(int ChoiceInt)
{
	PlayAnimMontage(M_Strafe[ChoiceInt]);
}

void AMageCharacter::SetAttackVariables()
{
	int32 random_min = 0;
	int32 random_max = 7;
	randomAttackCounter = FMath::RandRange(random_min,random_max);

	if(randomAttackCounter == 0) 
	{
		AttackDistance = 1250.f;
		AttackSpeed = 1.f;
		AttackDelay = FMath::RandRange(1.2f,1.6f);
		IsAttackingDelay = 0.7f;
	}
	else if(randomAttackCounter == 1)
	{
		AttackDistance = 1500.f;
		AttackSpeed = 1.f;
		AttackDelay = FMath::RandRange(1.5f,2.f);
		IsAttackingDelay = 0.7f;
	}
	else if(randomAttackCounter == 2)
	{
		if(playerRef)
		{
			
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),U_ParticleVfx[0],GetActorLocation(),GetActorRotation(),FVector(2.f));
			SetActorLocation(playerRef->GetActorLocation());
			SetActorRotation((playerRef->GetActorRotation()) * -1);
		}
		AttackDistance = 500.f;
		AttackSpeed = 1.4f;
		AttackDelay = FMath::RandRange(1.5f,2.f);
		IsAttackingDelay = 0.7f;
	}
	else if(randomAttackCounter == 3)
	{
		AttackDistance = 1900.f;
		AttackSpeed = 1.2f;
		AttackDelay = FMath::RandRange(1.5f,2.f);
		IsAttackingDelay = 0.7f;
	}
	else if(randomAttackCounter == 4)
	{
		AttackDistance = 1350.f;
		AttackSpeed = 1.3f;
		AttackDelay = FMath::RandRange(1.5f,2.f);
		IsAttackingDelay = 0.7f;
	}
	else if(randomAttackCounter == 5)
	{
		AttackDistance = 1250.f;
		AttackSpeed = 1.1f;
		AttackDelay = FMath::RandRange(1.5f,2.f);
		IsAttackingDelay = 0.7f;
	}
	else if(randomAttackCounter == 6)
	{
		AttackDistance = 350.f;
		AttackSpeed = 1.1f;
		AttackDelay = FMath::RandRange(2.f,2.5f);
		IsAttackingDelay = 0.7f;
	}
	else if(randomAttackCounter == 7)
	{
		AttackDistance = 1800.f;
		AttackSpeed = 1.1f;
		AttackDelay = FMath::RandRange(3.5f,4.5f);
		IsAttackingDelay = 0.7f;
	}
}


void AMageCharacter::AttackStart()
{
	IsAttacking = true;
}

void AMageCharacter::AttackEnd()
{
	IsAttacking = false;
}

void AMageCharacter::DodgeEvadeLeftRight()
{
	randomAttackCounter = FMath::RandRange(0,0);
	if(randomAttackCounter == 0)
	{
		PlayAnimMontage(M_Evade[FMath::RandRange(0,1)]);
	}
}

void AMageCharacter::DodgeEvadeBack(FName WhichAnim)
{
	randomAttackCounter = FMath::RandRange(0,0);
	if(randomAttackCounter == 0)
	{
		if(WhichAnim == "NormalEvade")
		{
			GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,TEXT("M_Evade 2 at!"));
			PlayAnimMontage(M_Evade[2]);
		}
		else if(WhichAnim == "EvadeAndAttack")
		{
			GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,TEXT("M_Evade 3 at!"));
			PlayAnimMontage(M_Evade[3]);
		}
	}
}

