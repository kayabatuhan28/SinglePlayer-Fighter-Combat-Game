// Fill out your copyright notice in the Description page of Project Settings.


#include "HeavyGroundSmash.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AHeavyGroundSmash::AHeavyGroundSmash()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractArea"));
	BoxComponent->SetupAttachment(GetRootComponent());

	SkillVfx = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Skillvfx"));
	SkillVfx->SetupAttachment(BoxComponent->GetAttachmentRoot());

}

// Called when the game starts or when spawned
void AHeavyGroundSmash::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this,&AHeavyGroundSmash::BeginOverleap);
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle,this,&AHeavyGroundSmash::Destroy,0.1f,false);
	
}

// Called every frame
void AHeavyGroundSmash::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHeavyGroundSmash::BeginOverleap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
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
			CloseCombatRef->getHeavyGroundSmashImpact(60.f,1.f);
			CloseCombatRef->WidgetRef->UpdateHp(CloseCombatRef->CurrentHealth,CloseCombatRef->MaxHealth);
		}
	}
	else if(OtherActor->ActorHasTag("Mage"))
	{
		MageRef = Cast<AMageCharacter>(OtherActor);
		if(MageRef )
		{
			MageRef->getBasicHit(50.f);
		}
	}
}

void AHeavyGroundSmash::Destroy()
{
	SetActorEnableCollision(false);
	//K2_DestroyActor();
}

