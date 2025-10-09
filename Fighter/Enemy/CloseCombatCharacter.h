// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "Fighter/FighterCharacter.h"
#include "Fighter/EnemyHealthBars/CloseCombatHpUI.h"
#include "GameFramework/Character.h"
#include "CloseCombatCharacter.generated.h"

UCLASS()
class FIGHTER_API ACloseCombatCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACloseCombatCharacter();

	void getComboBasicPunchLifeRegenerationHit(float Damage);
	void getComboFinalPunchLifeRegenerationHit(float Damage);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* HealthWidgetComp;

	AFighterCharacter* playerRef;
    
    UPROPERTY(BlueprintReadWrite)
	UCloseCombatHpUI* WidgetRef;

	UPROPERTY(BlueprintReadWrite,Category= Stats)
	float CurrentHealth = 500.f;
	UPROPERTY(BlueprintReadWrite,Category= Stats)
	float MaxHealth = 600.f;
	UPROPERTY(BlueprintReadWrite)
	float AttackSpeed = 1.f;
	UPROPERTY(BlueprintReadWrite)
	float AttackDistance = 1.f;
	UPROPERTY(BlueprintReadWrite)
	float AttackDelay = 1.f;

	UPROPERTY(BlueprintReadWrite)
	bool IsAttacking;

	bool IsDead;

	UPROPERTY(EditAnywhere,Category = Evades)
	TArray<UAnimMontage*> M_Evade;

	UPROPERTY(EditAnywhere,Category = HitAnims)
	TArray<UAnimMontage*> M_BasicHit;

	UPROPERTY(EditAnywhere,Category = HitAnims)
	TArray<UAnimMontage*> M_Hit;

	UPROPERTY(EditAnywhere,Category = Animations)
	TArray<UAnimMontage*> M_Attack;

	void getSpinKickHit(float Damage,float AnimSpeed);
	void getRunKickHit(float Damage,float AnimSpeed);
	void getHeavyGroundSmashImpact(float Damage,float AnimSpeed);
	void getBasicPunchHit(float Damage, float AnimSpeed);
	void getUpperCutPunchHit(float Damage, float AnimSpeed);
	void getKnockdownUppercut(float Damage, float AnimSpeed);
	void getGroundSmashHit(float Damage, float AnimSpeed);

	UFUNCTION(BlueprintCallable)
	void Attacks();
	UFUNCTION(BlueprintCallable)
	void SetAttackVariables();
	int randomAttackCounter;

	UFUNCTION(BlueprintCallable)
	void AttackStart();
	UFUNCTION(BlueprintCallable)
	void AttackEnd();
	
	

};




