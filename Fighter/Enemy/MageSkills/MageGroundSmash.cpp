// Fill out your copyright notice in the Description page of Project Settings.


#include "MageGroundSmash.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AMageGroundSmash::AMageGroundSmash()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("InteractCollision"));
	SphereComponent->SetupAttachment(GetRootComponent());

	SkillVfx = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SkillVfx"));
	SkillVfx->SetupAttachment(SphereComponent->GetAttachmentRoot());

}

// Called when the game starts or when spawned
void AMageGroundSmash::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&AMageGroundSmash::BeginOverleap);
	GetWorld()->GetTimerManager().SetTimer(MyTimerHandle,this,&AMageGroundSmash::DestroyTime,0.5f,false);
	
}

// Called every frame
void AMageGroundSmash::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMageGroundSmash::BeginOverleap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("Player"))
	{
		PlayerRef = Cast<AFighterCharacter>(OtherActor);
		if(PlayerRef )
		{
			PlayerRef->getKnockBackHit(55.f,0.6f);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),HitParticle,PlayerRef->GetActorLocation(),GetActorRotation(),FVector(1.5f));
			SphereComponent->SetCollisionProfileName("NoCollision");
		}
	}
}

void AMageGroundSmash::DestroyTime()
{
	K2_DestroyActor();
}

