// Fill out your copyright notice in the Description page of Project Settings.


#include "Fly4HeavyProjectile.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AFly4HeavyProjectile::AFly4HeavyProjectile()
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
void AFly4HeavyProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&AFly4HeavyProjectile::BeginOverleap);
	GetWorld()->GetTimerManager().SetTimer(MyTimerHandle,this,&AFly4HeavyProjectile::DestroyTime,4.f,false);
}

// Called every frame
void AFly4HeavyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFly4HeavyProjectile::BeginOverleap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("Player"))
	{
		PlayerRef = Cast<AFighterCharacter>(OtherActor);
		if(PlayerRef )
		{
			PlayerRef->getKnockDownHit(50.f,1.f);
			SphereComponent->SetCollisionProfileName("NoCollision");
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),HitParticle,PlayerRef->GetActorLocation(),GetActorRotation(),FVector(2.f));
			K2_DestroyActor();
		}
	}
}

void AFly4HeavyProjectile::DestroyTime()
{
	K2_DestroyActor();
}

