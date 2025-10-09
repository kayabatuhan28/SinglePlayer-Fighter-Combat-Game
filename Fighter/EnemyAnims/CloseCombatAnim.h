// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Fighter/Enemy/CloseCombatCharacter.h"
#include "CloseCombatAnim.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTER_API UCloseCombatAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly)
	ACloseCombatCharacter* EnemyRef;

	UPROPERTY(BlueprintReadOnly)
	float Speed;
	UPROPERTY(BlueprintReadOnly)
	float Direction;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AActor>> SkillsActor;

	UFUNCTION(BlueprintCallable)
	void CastBasicRightKick(); // Index 0

	UFUNCTION(BlueprintCallable)
	void CastBasicRightPunch(); // Index 1

	
};
