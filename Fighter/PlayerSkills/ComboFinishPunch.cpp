// Fill out your copyright notice in the Description page of Project Settings.


#include "ComboFinishPunch.h"

// Sets default values
AComboFinishPunch::AComboFinishPunch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("HitArea"));
	SphereComponent->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AComboFinishPunch::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&AComboFinishPunch::BeginOverleap);
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle,this,&AComboFinishPunch::Destroy,0.2f,false);
	
}

// Called every frame
void AComboFinishPunch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AComboFinishPunch::BeginOverleap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("CloseCombat"))
	{
		CloseCombatRef = Cast<ACloseCombatCharacter>(OtherActor);
		if(CloseCombatRef)
		{
			CloseCombatRef->getComboFinalPunchLifeRegenerationHit(30.f);
			CloseCombatRef->WidgetRef->UpdateHp(CloseCombatRef->CurrentHealth,CloseCombatRef->MaxHealth);
		}
	}
}

void AComboFinishPunch::Destroy()
{
	K2_DestroyActor();
}

