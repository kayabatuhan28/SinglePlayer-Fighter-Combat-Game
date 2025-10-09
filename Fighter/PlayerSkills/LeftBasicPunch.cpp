// Fill out your copyright notice in the Description page of Project Settings.


#include "LeftBasicPunch.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ALeftBasicPunch::ALeftBasicPunch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("HitArea"));
	SphereComponent->SetupAttachment(GetRootComponent());
	
	

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&ALeftBasicPunch::BeginOverleap);

}


void ALeftBasicPunch::BeginPlay()
{
	Super::BeginPlay();
	
}


void ALeftBasicPunch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALeftBasicPunch::BeginOverleap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("CloseCombat"))
	{
		CloseCombatRef = Cast<ACloseCombatCharacter>(OtherActor);
		if(CloseCombatRef)
		{
			CloseCombatRef->getBasicPunchHit(20.f,1.f);
			CloseCombatRef->WidgetRef->UpdateHp(CloseCombatRef->CurrentHealth,CloseCombatRef->MaxHealth);
		}
	}
	else if(OtherActor->ActorHasTag("Mage"))
	{
		MageRef = Cast<AMageCharacter>(OtherActor);
		if(MageRef )
		{
			MageRef->getBasicHitNoAnim(25.f);
		}
	}
}

