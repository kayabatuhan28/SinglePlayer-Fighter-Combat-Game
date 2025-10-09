// Fill out your copyright notice in the Description page of Project Settings.


#include "GroundSmash.h"

// Sets default values
AGroundSmash::AGroundSmash()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("HitArea"));
	SphereComponent->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AGroundSmash::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&AGroundSmash::BeginOverleap);
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle,this,&AGroundSmash::Destroy,0.2f,false);
	
}

// Called every frame
void AGroundSmash::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGroundSmash::BeginOverleap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("CloseCombat"))
	{
		CloseCombatRef = Cast<ACloseCombatCharacter>(OtherActor);
		if(CloseCombatRef)
		{
			CloseCombatRef->getGroundSmashHit(65.f,1.f);
			CloseCombatRef->WidgetRef->UpdateHp(CloseCombatRef->CurrentHealth,CloseCombatRef->MaxHealth);
		}
	}
	else if(OtherActor->ActorHasTag("Mage"))
	{
		MageRef = Cast<AMageCharacter>(OtherActor);
		if(MageRef )
		{
			MageRef->getKnockBackHit(50.f);
		}
	}
}

void AGroundSmash::Destroy()
{
	K2_DestroyActor();
}

