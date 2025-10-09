// Fill out your copyright notice in the Description page of Project Settings.


#include "MageFlyGroundSmashSkill.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AMageFlyGroundSmashSkill::AMageFlyGroundSmashSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("InteractCollision"));
	SphereComponent->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AMageFlyGroundSmashSkill::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&AMageFlyGroundSmashSkill::BeginOverleap);
	GetWorld()->GetTimerManager().SetTimer(MyTimerHandle,this,&AMageFlyGroundSmashSkill::DestroyTime,0.5f,false);
	
}

// Called every frame
void AMageFlyGroundSmashSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMageFlyGroundSmashSkill::BeginOverleap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("Player"))
	{
		PlayerRef = Cast<AFighterCharacter>(OtherActor);
		if(PlayerRef )
		{
			PlayerRef->getKnockDownHit(70.f,0.6f);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),HitParticle,PlayerRef->GetActorLocation(),GetActorRotation(),FVector(1.5f));
			SphereComponent->SetCollisionProfileName("NoCollision");
		}
	}
}

void AMageFlyGroundSmashSkill::DestroyTime()
{
	K2_DestroyActor();
}

