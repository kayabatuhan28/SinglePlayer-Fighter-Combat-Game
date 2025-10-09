// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Fighter/Enemy/MageCharacter.h"
#include "MageAnim.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTER_API UMageAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	virtual void NativeBeginPlay() override;
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly)
	AMageCharacter* MageRef;

	AFighterCharacter* playerRef;
	
	UPROPERTY(BlueprintReadOnly)
	float Speed;
	UPROPERTY(BlueprintReadOnly)
	float Direction;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AActor>> SkillsActor;

	UFUNCTION(BlueprintCallable)
	void CastPrimaryAttack(); // Index 0

	UFUNCTION(BlueprintCallable)
	void CastBackDashAndPrimaryAttack(); // Index 1

	UFUNCTION(BlueprintCallable)
	void CastGroundSmash(); // Index 2

	UFUNCTION(BlueprintCallable)
	void CastFrostArea(); // Index 3

	UFUNCTION(BlueprintCallable)
	void CastFlyGroundSmash(); // Index 4

	UFUNCTION(BlueprintCallable)
	void CastHeavyProjectile(); // Index 5

	UFUNCTION(BlueprintCallable)
	void CastFly4SmallProjectile(); // Index 6

	UFUNCTION(BlueprintCallable)
	void CastFly4BigProjectile(); // Index 7
};
