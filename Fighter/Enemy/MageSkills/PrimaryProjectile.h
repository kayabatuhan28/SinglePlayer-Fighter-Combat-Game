// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Fighter/FighterCharacter.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PrimaryProjectile.generated.h"

UCLASS()
class FIGHTER_API APrimaryProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APrimaryProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AFighterCharacter* PlayerRef;
	
	UPROPERTY(EditDefaultsOnly)
    USphereComponent* SphereComponent;
    
    UPROPERTY(EditDefaultsOnly)
    UProjectileMovementComponent* ProjectileMovementComponent;
    
    UPROPERTY(EditDefaultsOnly)
    UParticleSystem* HitParticle;
    
    UPROPERTY(EditDefaultsOnly)
    UParticleSystemComponent* SkillVfx;
    	
    UFUNCTION()
	void BeginOverleap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
    
	FTimerHandle MyTimerHandle;
	void DestroyTime();

};
