// Fill out your copyright notice in the Description page of Project Settings.


#include "PrimaryProjectile.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
APrimaryProjectile::APrimaryProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("InteractCollision"));
	SphereComponent->SetupAttachment(GetRootComponent());

	SkillVfx = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SkillVfx"));
	SkillVfx->SetupAttachment(SphereComponent->GetAttachmentRoot());

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(SphereComponent);
	ProjectileMovementComponent->InitialSpeed = 3500.f;
	ProjectileMovementComponent->MaxSpeed = 3500.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;

}

// Called when the game starts or when spawned
void APrimaryProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&APrimaryProjectile::BeginOverleap);
	GetWorld()->GetTimerManager().SetTimer(MyTimerHandle,this,&APrimaryProjectile::DestroyTime,4.f,false);
	
}

// Called every frame
void APrimaryProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APrimaryProjectile::BeginOverleap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("Player"))
	{
		GetWorld()->GetTimerManager().SetTimer(MyTimerHandle,this,&APrimaryProjectile::DestroyTime,0.1f,false);
		PlayerRef = Cast<AFighterCharacter>(OtherActor);
		if(PlayerRef )
		{
			PlayerRef->getBasicHit(30.f,0.6f);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),HitParticle,PlayerRef->GetActorLocation(),GetActorRotation(),FVector(1.5f));
			K2_DestroyActor();
		}
	}
}

void APrimaryProjectile::DestroyTime()
{
	K2_DestroyActor();
}

