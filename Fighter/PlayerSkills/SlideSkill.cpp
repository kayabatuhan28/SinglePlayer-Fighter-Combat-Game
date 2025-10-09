// Fill out your copyright notice in the Description page of Project Settings.


#include "SlideSkill.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ASlideSkill::ASlideSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("HitArea"));
	SphereComponent->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ASlideSkill::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&ASlideSkill::BeginOverleap);
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle,this,&ASlideSkill::Destroy,1.f,false);
	
}

// Called every frame
void ASlideSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASlideSkill::BeginOverleap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("CloseCombat"))
	{
		CloseCombatRef = Cast<ACloseCombatCharacter>(OtherActor);
		if(CloseCombatRef)
		{
			FVector Scale = FVector(3.5f);
			FRotator Rot = GetActorRotation();
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),HitParticle,OtherActor->GetActorLocation(),Rot,Scale);
			CloseCombatRef->getGroundSmashHit(60.f,1.f);
			CloseCombatRef->WidgetRef->UpdateHp(CloseCombatRef->CurrentHealth,CloseCombatRef->MaxHealth);
		}
	}
	else if(OtherActor->ActorHasTag("Mage"))
	{
		MageRef = Cast<AMageCharacter>(OtherActor);
		if(MageRef )
		{
			MageRef->getKnockDownHit(70.f);
		}
	}
}

void ASlideSkill::Destroy()
{
	K2_DestroyActor();
}

