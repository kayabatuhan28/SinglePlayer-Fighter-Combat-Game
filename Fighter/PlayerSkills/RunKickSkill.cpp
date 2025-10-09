// Fill out your copyright notice in the Description page of Project Settings.


#include "RunKickSkill.h"

// Sets default values
ARunKickSkill::ARunKickSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("HitArea"));
	SphereComponent->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ARunKickSkill::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&ARunKickSkill::BeginOverleap);
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle,this,&ARunKickSkill::Destroy,0.2f,false);
	
}

// Called every frame
void ARunKickSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARunKickSkill::BeginOverleap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("CloseCombat"))
	{
		CloseCombatRef = Cast<ACloseCombatCharacter>(OtherActor);
		if(CloseCombatRef)
		{
			CloseCombatRef->getRunKickHit(25.f,1.f);
			CloseCombatRef->WidgetRef->UpdateHp(CloseCombatRef->CurrentHealth,CloseCombatRef->MaxHealth);
		}
	}
}

void ARunKickSkill::Destroy()
{
	K2_DestroyActor();
}

