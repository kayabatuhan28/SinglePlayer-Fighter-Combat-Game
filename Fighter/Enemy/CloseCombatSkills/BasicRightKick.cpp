// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicRightKick.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ABasicRightKick::ABasicRightKick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("HitArea"));
	SphereComponent->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ABasicRightKick::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&ABasicRightKick::BeginOverleap);
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle,this,&ABasicRightKick::Destroy,0.2f,false);
	
}

// Called every frame
void ABasicRightKick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasicRightKick::BeginOverleap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("Player"))
	{
		playerRef = Cast<AFighterCharacter>(OtherActor);
		if(playerRef)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),HitParticle,OtherActor->GetActorLocation(),GetActorRotation(),FVector(1.5));
			playerRef->getBasicHit(25.f,0.7f);
		}
	}
}

void ABasicRightKick::Destroy()
{
	K2_DestroyActor();
}

