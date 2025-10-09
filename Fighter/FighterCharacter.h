// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FighterCharacter.generated.h"

UCLASS(config=Game)
class AFighterCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AFighterCharacter();

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

	//Functions
	void SprintStart();
	void SprintEnd();
	void EquippedWeapon();
	void SlowWalkSet();
	void SlowWalkUnSet();

	void LeftBasicPunch();
	void UpperCut();
	void KnockdownUpperCut();
	void GroundSmash();
	void FlyGroundSmash();
	void AduketSkill();
	void ComboPunchLifeRegeneration();
	void SliderSkill();
	void HeavyGroundSmashSkill();
	void RunKick();
	void SpinningKick();
	void SummonSpirit();
	
	void IsWPressed();
	void IsSPressed();
	void IsAPressed();
	void IsDPressed();
	void IsUnWPressed();
	void IsUnSPressed();
	void IsUnAPressed();
	void IsUnDPressed();
	void Evade();

	void getBasicHitNoAnim(float Damage, float ReAttackTimer);
	void getBasicHit(float Damage, float ReAttackTimer);
	void getKnockBackHit(float Damage,float ReAttackTimer);
	void getKnockDownHit(float Damage,float ReAttackTimer);
	FTimerHandle SetIceAreaHitTimer;
	void IceAreaIn();
	void getIceAreaHit();
	void CleargetIceAreaHit();

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	

public:
	
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	UPROPERTY(BlueprintReadWrite,Category= Stats)
	bool IsAttacking;
	bool IsSprint;
	UPROPERTY(BlueprintReadWrite,Category= Boolean)
	bool WeaponEquipped;
	bool WPressed;
	bool SPressed;
	bool APressed;
	bool DPressed;
	bool ısDead;
	
	UPROPERTY(BlueprintReadWrite,Category= Stats)
	float CurrentHealth = 200.f;
	UPROPERTY(BlueprintReadWrite,Category= Stats)
	float MaxHealth = 300.f;
	UPROPERTY(BlueprintReadWrite,Category= Stats)
	float CurrentStamina = 350.f;
	UPROPERTY(BlueprintReadWrite,Category= Stats)
	float MaxStamina = 350.f;

	UPROPERTY(EditAnywhere,Category = Evades)
	TArray<UAnimMontage*> M_Evade;

	UPROPERTY(EditAnywhere,Category = HitAnims)
	TArray<UAnimMontage*> M_Hit;

	UPROPERTY(EditAnywhere,Category = Attacks)
	TArray<UAnimMontage*> M_Attack;

	UPROPERTY(EditAnywhere,Category = Vfx)
	TArray<UParticleSystem*> U_ParticleVfx;

	UPROPERTY(EditAnywhere,Category = Equip)
	UAnimMontage* M_EquipWeapon;
	UPROPERTY(EditAnywhere,Category = Equip)	
	UAnimMontage* M_UnEquipWeapon;

	UPROPERTY(EditAnywhere,Category = Die)	
	UAnimMontage* M_Die;

	int AttackCount;
	int UpperCutCount;

	FTimerHandle PlayerAttackTimer;
	void SetIsAttackingAfterHit();
	
};











