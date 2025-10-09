// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fighter/FighterCharacter.h"
#include "GameFramework/Character.h"
#include "MageCharacter.generated.h"

UCLASS()
class FIGHTER_API AMageCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMageCharacter();

	void getBasicHitNoAnim(float Damage);
	void getBasicHit(float Damage);
	void getKnockBackHit(float Damage);
	void getKnockDownHit(float Damage);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	AFighterCharacter* playerRef;
	
	UPROPERTY(BlueprintReadWrite,Category= Stats)
	float CurrentHealth = 800.f;
	UPROPERTY(BlueprintReadWrite,Category= Stats)
	float MaxHealth = 800.f;
	UPROPERTY(BlueprintReadWrite)
	float AttackSpeed = 1.f;
	UPROPERTY(BlueprintReadWrite)
	float AttackDistance = 1.f;
	UPROPERTY(BlueprintReadWrite)
	float AttackDelay = 1.f;
	UPROPERTY(BlueprintReadWrite)
	float IsAttackingDelay;

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

	UPROPERTY(EditAnywhere,Category = Animations)
	TArray<UAnimMontage*> M_Strafe;

	UPROPERTY(EditAnywhere,Category = Vfx)
	TArray<UParticleSystem*> U_ParticleVfx; // 0 GroundSmash TpVfx

	UFUNCTION(BlueprintCallable)
	void Attacks();
	UFUNCTION(BlueprintCallable)
	void SetAttackVariables();
	
	void Strafe(int ChoiceInt);
	int randomAttackCounter;
	int randomStrafeCounter;

	UFUNCTION(BlueprintCallable)
	void AttackStart();
	UFUNCTION(BlueprintCallable)
	void AttackEnd();

	UFUNCTION(BlueprintCallable)
	void DodgeEvadeLeftRight();

	UFUNCTION(BlueprintCallable)
	void DodgeEvadeBack(FName WhichAnim);

};
