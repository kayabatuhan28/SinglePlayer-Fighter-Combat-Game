// Fill out your copyright notice in the Description page of Project Settings.


#include "Aduket.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AAduket::AAduket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("InteractCollision"));
	SphereComponent->SetupAttachment(GetRootComponent());

	SkillVfx = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SkillVfx"));
	SkillVfx->SetupAttachment(SphereComponent->GetAttachmentRoot());

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(SphereComponent);
	ProjectileMovementComponent->InitialSpeed = 3000.f;
	ProjectileMovementComponent->MaxSpeed = 3000.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;

}

// Called when the game starts or when spawned
void AAduket::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&AAduket::BeginOverleap);
	GetWorld()->GetTimerManager().SetTimer(MyTimerHandle,this,&AAduket::DestroyTime,3.f,false);

}

// Called every frame
void AAduket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAduket::Destroyed()
{
	Super::Destroyed();
	FVector Scale = FVector(1.5f);
	FRotator Rot = GetActorRotation();
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),HitParticle,GetActorLocation(),Rot,Scale);
	
}

void AAduket::BeginOverleap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("CloseCombat"))
	{
		GetWorld()->GetTimerManager().SetTimer(MyTimerHandle,this,&AAduket::DestroyTime,0.0000001f,false);
		CloseCombatRef = Cast<ACloseCombatCharacter>(OtherActor);
		if(CloseCombatRef )
		{
			
			CloseCombatRef->getKnockdownUppercut(80.f,0.3f);
			CloseCombatRef->WidgetRef->UpdateHp(CloseCombatRef->CurrentHealth,CloseCombatRef->MaxHealth);
			
		}
	}
	else if(OtherActor->ActorHasTag("Mage"))
	{
		MageRef = Cast<AMageCharacter>(OtherActor);
		if(MageRef )
		{
			MageRef->getKnockBackHit(70.f);
		}
	}
}

void AAduket::DestroyTime()
{
	K2_DestroyActor();
}

