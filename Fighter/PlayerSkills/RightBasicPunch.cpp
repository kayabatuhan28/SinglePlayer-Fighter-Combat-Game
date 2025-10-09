// Fill out your copyright notice in the Description page of Project Settings.


#include "RightBasicPunch.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ARightBasicPunch::ARightBasicPunch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("HitArea"));
	SphereComponent->SetupAttachment(GetRootComponent());
	
	

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&ARightBasicPunch::BeginOverleap);

}

// Called when the game starts or when spawned
void ARightBasicPunch::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle,this,&ARightBasicPunch::Destroy,0.2f,false);
	
}

// Called every frame
void ARightBasicPunch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARightBasicPunch::BeginOverleap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("CloseCombat"))
	{
		CloseCombatRef = Cast<ACloseCombatCharacter>(OtherActor);
		if(CloseCombatRef)
		{
			CloseCombatRef->getBasicPunchHit(20.f,1.f);
			CloseCombatRef->WidgetRef->UpdateHp(CloseCombatRef->CurrentHealth,CloseCombatRef->MaxHealth);
		}	}
}

void ARightBasicPunch::Destroy()
{
	K2_DestroyActor();
}

