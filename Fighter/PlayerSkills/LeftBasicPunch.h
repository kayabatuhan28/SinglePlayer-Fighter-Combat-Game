// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Fighter/Enemy/CloseCombatCharacter.h"
#include "Fighter/Enemy/MageCharacter.h"
#include "GameFramework/Actor.h"
#include "LeftBasicPunch.generated.h"

UCLASS()
class FIGHTER_API ALeftBasicPunch : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ALeftBasicPunch();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	ACloseCombatCharacter* CloseCombatRef;
	AMageCharacter* MageRef;

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* HitParticle;
	
	UFUNCTION()
	void BeginOverleap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
};
