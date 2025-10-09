// Fill out your copyright notice in the Description page of Project Settings.


#include "CloseCombatCharacter.h"

#include "Fighter/EnemyHealthBars/CloseCombatHpUI.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACloseCombatCharacter::ACloseCombatCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HealthWidgetComp->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);

}



// Called when the game starts or when spawned
void ACloseCombatCharacter::BeginPlay()
{
	Super::BeginPlay();
	playerRef = Cast<AFighterCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	
	WidgetRef =	Cast<UCloseCombatHpUI>(HealthWidgetComp->GetUserWidgetObject());
	WidgetRef->UpdateHp(CurrentHealth,MaxHealth);
}

// Called every frame
void ACloseCombatCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACloseCombatCharacter::getSpinKickHit(float Damage, float AnimSpeed)
{
	if(CurrentHealth - Damage <= 0 && IsDead == false)
	{
		IsDead = true;
		CurrentHealth = 0;
	}
	else
	{
		CurrentHealth -= Damage;
		M_Hit[3]->RateScale = 0.8f;
		PlayAnimMontage(M_Hit[3]);
	}
}

void ACloseCombatCharacter::getRunKickHit(float Damage, float AnimSpeed)
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

void ACloseCombatCharacter::getHeavyGroundSmashImpact(float Damage, float AnimSpeed)
{
	if(CurrentHealth - Damage <= 0 && IsDead == false)
	{
		IsDead = true;
		CurrentHealth = 0;
	}
	else
	{
		CurrentHealth -= Damage;
		PlayAnimMontage(M_Hit[2]);
	}
}

void ACloseCombatCharacter::getBasicPunchHit(float Damage, float AnimSpeed)
{
	if(CurrentHealth - Damage <= 0 && IsDead == false)
	{
		IsDead = true;
		CurrentHealth = 0;
	}
	else
	{
		CurrentHealth -= Damage;
		PlayAnimMontage(M_BasicHit[0]);
	}
}

void ACloseCombatCharacter::getUpperCutPunchHit(float Damage, float AnimSpeed)
{
	if(CurrentHealth - Damage <= 0 && IsDead == false)
	{
		IsDead = true;
		CurrentHealth = 0;
	}
	else
	{
		CurrentHealth -= Damage;
		PlayAnimMontage(M_BasicHit[1]);
	}
}

void ACloseCombatCharacter::getKnockdownUppercut(float Damage, float AnimSpeed)
{
	
	if(CurrentHealth - Damage <= 0 && IsDead == false)
	{
		IsDead = true;
		CurrentHealth = 0;
	}
	else
	{
		CurrentHealth -= Damage;
		M_Hit[0]->RateScale = AnimSpeed;
		PlayAnimMontage(M_Hit[0]);
	}
}

void ACloseCombatCharacter::getGroundSmashHit(float Damage, float AnimSpeed)
{
	if(CurrentHealth - Damage <= 0 && IsDead == false)
	{
		IsDead = true;
		CurrentHealth = 0;
	}
	else
	{
		CurrentHealth -= Damage;
		PlayAnimMontage(M_Hit[1]);
	}
}

void ACloseCombatCharacter::Attacks()
{
	if(randomAttackCounter == 0)
	{
		M_Attack[0]->RateScale = AttackSpeed;
		PlayAnimMontage(M_Attack[0]);
	}
	if(randomAttackCounter == 1)
	{
		M_Attack[1]->RateScale = AttackSpeed;
		PlayAnimMontage(M_Attack[1]);
	}
}

void ACloseCombatCharacter::SetAttackVariables()
{
	int32 random_min = 0;
	int32 random_max = 1;
	randomAttackCounter = FMath::RandRange(random_min,random_max);

	if(randomAttackCounter == 0) 
	{
		AttackDistance = 25.f;
		AttackSpeed = 1.f;
		AttackDelay = FMath::RandRange(1.8f,2.2f);
	}
	if(randomAttackCounter == 1) 
	{
		AttackDistance = 35.f;
		AttackSpeed = 1.f;
		AttackDelay = FMath::RandRange(1.8f,2.2f);
	}
}

void ACloseCombatCharacter::AttackStart()
{
	IsAttacking = true;
}

void ACloseCombatCharacter::AttackEnd()
{
	IsAttacking = false;
}

void ACloseCombatCharacter::getComboBasicPunchLifeRegenerationHit(float Damage)
{
	if(CurrentHealth - Damage <= 0 && IsDead == false)
	{
		IsDead = true;
		CurrentHealth = 0;
	}
	else
	{
		if(playerRef)
		{
			CurrentHealth -= Damage;
			PlayAnimMontage(M_BasicHit[0]);
			if(playerRef->CurrentHealth + Damage/3 >= playerRef->MaxHealth)
			{
				playerRef->CurrentHealth = playerRef->MaxHealth;
			}
			else
			{
				playerRef->CurrentHealth += Damage/3;
			}
		}
	}
}

void ACloseCombatCharacter::getComboFinalPunchLifeRegenerationHit(float Damage)
{
	if(CurrentHealth - Damage <= 0 && IsDead == false)
	{
		IsDead = true;
		CurrentHealth = 0;
	}
	else
	{
		if(playerRef)
		{
			CurrentHealth -= Damage;
			M_Hit[0]->RateScale = 1.f;
			PlayAnimMontage(M_Hit[0]);
			if(playerRef->CurrentHealth + Damage/2 >= playerRef->MaxHealth)
			{
				playerRef->CurrentHealth = playerRef->MaxHealth;
			}
			else
			{
				playerRef->CurrentHealth += Damage/2;
			}
		}
	}
}

