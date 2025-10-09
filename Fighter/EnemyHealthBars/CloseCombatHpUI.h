// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "CloseCombatHpUI.generated.h"


UCLASS()
class FIGHTER_API UCloseCombatHpUI : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativePreConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	UProgressBar* HealthBar;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* CurrentHealthLabel;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* EnemyNameLabel;

	UFUNCTION(BlueprintCallable)
	void UpdateHp(float Health,float MaxHealth);
	
};
