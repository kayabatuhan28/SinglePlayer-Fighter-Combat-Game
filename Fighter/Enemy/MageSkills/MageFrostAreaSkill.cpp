// Fill out your copyright notice in the Description page of Project Settings.


#include "MageFrostAreaSkill.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AMageFrostAreaSkill::AMageFrostAreaSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("InteractCollision"));
	SphereComponent->SetupAttachment(GetRootComponent());

	SkillVfx = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SkillVfx"));
	SkillVfx->SetupAttachment(SphereComponent->GetAttachmentRoot());

}

// Called when the game starts or when spawned
void AMageFrostAreaSkill::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&AMageFrostAreaSkill::BeginOverleap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this,&AMageFrostAreaSkill::OnOverlapEnd);
	GetWorld()->GetTimerManager().SetTimer(MyTimerHandle,this,&AMageFrostAreaSkill::DestroyTime,4.f,false);
}

// Called every frame
void AMageFrostAreaSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMageFrostAreaSkill::BeginOverleap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("Player"))
	{
		PlayerRef = Cast<AFighterCharacter>(OtherActor);
		if(PlayerRef )
		{
			PlayerRef->IceAreaIn();
			PlayerRef->GetCharacterMovement()->MaxWalkSpeed = 200.f;
		}
	}
}

void AMageFrostAreaSkill::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor->ActorHasTag("Player"))
	{
		PlayerRef = Cast<AFighterCharacter>(OtherActor);
		if(PlayerRef )
		{
			PlayerRef->CleargetIceAreaHit();
			PlayerRef->GetCharacterMovement()->MaxWalkSpeed = 450.f;
		}
	}
}

void AMageFrostAreaSkill::DestroyTime()
{
	PlayerRef = Cast<AFighterCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	if(PlayerRef )
	{
		PlayerRef->GetCharacterMovement()->MaxWalkSpeed = 450.f;
	}
	K2_DestroyActor();
}

