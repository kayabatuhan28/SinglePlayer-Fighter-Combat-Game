// Fill out your copyright notice in the Description page of Project Settings.


#include "ComboLeftPunch.h"

// Sets default values
AComboLeftPunch::AComboLeftPunch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("HitArea"));
	SphereComponent->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AComboLeftPunch::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&AComboLeftPunch::BeginOverleap);
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle,this,&AComboLeftPunch::Destroy,0.2f,false);
	
}

// Called every frame
void AComboLeftPunch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AComboLeftPunch::BeginOverleap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("CloseCombat"))
	{
		CloseCombatRef = Cast<ACloseCombatCharacter>(OtherActor);
		if(CloseCombatRef)
		{
			CloseCombatRef->getComboBasicPunchLifeRegenerationHit(10.f);
			CloseCombatRef->WidgetRef->UpdateHp(CloseCombatRef->CurrentHealth,CloseCombatRef->MaxHealth);
		}
	}
}

void AComboLeftPunch::Destroy()
{
	K2_DestroyActor();
}

