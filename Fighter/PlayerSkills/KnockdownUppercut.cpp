// Fill out your copyright notice in the Description page of Project Settings.


#include "KnockdownUppercut.h"

// Sets default values
AKnockdownUppercut::AKnockdownUppercut()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("HitArea"));
	SphereComponent->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AKnockdownUppercut::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&AKnockdownUppercut::BeginOverleap);
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle,this,&AKnockdownUppercut::Destroy,0.2f,false);
	
}

// Called every frame
void AKnockdownUppercut::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKnockdownUppercut::BeginOverleap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("CloseCombat"))
	{
		CloseCombatRef = Cast<ACloseCombatCharacter>(OtherActor);
		if(CloseCombatRef)
		{
			CloseCombatRef->getKnockdownUppercut(40.f,1.f);
			CloseCombatRef->WidgetRef->UpdateHp(CloseCombatRef->CurrentHealth,CloseCombatRef->MaxHealth);
		}
	}
}

void AKnockdownUppercut::Destroy()
{
	K2_DestroyActor();
}

