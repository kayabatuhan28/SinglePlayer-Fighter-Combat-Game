// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Fighter/Enemy/CloseCombatCharacter.h"
#include "GameFramework/Actor.h"
#include "RightBasicPunch.generated.h"

UCLASS()
class FIGHTER_API ARightBasicPunch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARightBasicPunch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	ACloseCombatCharacter* CloseCombatRef;

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* HitParticle;

	

	UFUNCTION()
	void BeginOverleap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	FTimerHandle DestroyTimerHandle;
	void Destroy();

};
