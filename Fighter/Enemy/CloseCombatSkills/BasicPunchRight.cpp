// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicPunchRight.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ABasicPunchRight::ABasicPunchRight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("HitArea"));
	SphereComponent->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ABasicPunchRight::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&ABasicPunchRight::BeginOverleap);
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle,this,&ABasicPunchRight::Destroy,0.2f,false);
	
}

// Called every frame
void ABasicPunchRight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasicPunchRight::BeginOverleap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("Player"))
	{
		playerRef = Cast<AFighterCharacter>(OtherActor);
		if(playerRef)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),HitParticle,OtherActor->GetActorLocation(),GetActorRotation(),FVector(1));
			playerRef->getBasicHitNoAnim(15.f,0.3f);
		}
	}
}

void ABasicPunchRight::Destroy()
{
	K2_DestroyActor();
}

