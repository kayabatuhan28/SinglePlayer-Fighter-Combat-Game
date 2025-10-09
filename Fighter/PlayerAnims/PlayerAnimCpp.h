// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Fighter/FighterCharacter.h"
#include "PlayerAnimCpp.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTER_API UPlayerAnimCpp : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadWrite)
	AFighterCharacter* playerRef;

	UFUNCTION(BlueprintCallable)
	void AttackStart();
	UFUNCTION(BlueprintCallable)
	void AttackEnd();
	
	UFUNCTION(BlueprintCallable)
	void FlyOn();
	UFUNCTION(BlueprintCallable)
	void FlyOff();

	UFUNCTION(BlueprintCallable)
	void CameraZoomOut();
	UFUNCTION(BlueprintCallable)
	void CameraZoomIn();
	
	UPROPERTY(BlueprintReadOnly)
	float Speed;
	UPROPERTY(BlueprintReadOnly)
	float Direction;
	UPROPERTY(BlueprintReadOnly)
	bool IsInAir;
	UPROPERTY(BlueprintReadOnly)
	bool EquippedWeapon;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AActor>> SkillsActor;

	UFUNCTION(BlueprintCallable)
	void CastLeftBasicPunch(); // Index 0

	UFUNCTION(BlueprintCallable)
	void CastRightBasicPunch(); // Index 1

	UFUNCTION(BlueprintCallable)
	void CastUpperCutPunch(); // Index 2
	
	UFUNCTION(BlueprintCallable)
	void CastKnockdownUpperCut(); // Index 3

	UFUNCTION(BlueprintCallable)
	void CastGroundSmash(); // Index 4

	UFUNCTION(BlueprintCallable)
	void CastAduket(); // Index 5

	UFUNCTION(BlueprintCallable)
	void CastComboBasicPunchRight(); // Index 6

	UFUNCTION(BlueprintCallable)
	void CastComboBasicPunchLeft(); // Index 7

	UFUNCTION(BlueprintCallable)
	void CastComboFinalPunch(); // Index 8

	UFUNCTION(BlueprintCallable)
	void CastSliderSkill(); // Index 9

	UFUNCTION(BlueprintCallable)
	void CastHeavyGroundSmash(); // Index 10

	UFUNCTION(BlueprintCallable)
	void CastRunKick(); // Index 11

	UFUNCTION(BlueprintCallable)
	void CastSpinningKick(); // Index 12

	UFUNCTION(BlueprintCallable)
	void CastSummon1(); // Index 13

	UFUNCTION(BlueprintCallable)
	void CastSummon2(); // Index 14

	UFUNCTION(BlueprintCallable)
	void CastSummon3(); // Index 15
};
