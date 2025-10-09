// Fill out your copyright notice in the Description page of Project Settings.


#include "Summon3.h"

// Sets default values
ASummon3::ASummon3()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("HitArea"));
	SphereComponent->SetupAttachment(GetRootComponent());

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SkeletalMeshComponent->SetupAttachment(SphereComponent->GetAttachmentRoot());

}

// Called when the game starts or when spawned
void ASummon3::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&ASummon3::BeginOverleap);
	
}

// Called every frame
void ASummon3::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASummon3::BeginOverleap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("CloseCombat"))
	{
		CloseCombatRef = Cast<ACloseCombatCharacter>(OtherActor);
		if(CloseCombatRef)
		{
			CloseCombatRef->getGroundSmashHit(45.f,1.f);
			CloseCombatRef->WidgetRef->UpdateHp(CloseCombatRef->CurrentHealth,CloseCombatRef->MaxHealth);
		}
	}
}

