// Fill out your copyright notice in the Description page of Project Settings.


#include "CloseCombatHpUI.h"

void UCloseCombatHpUI::NativePreConstruct()
{
	Super::NativePreConstruct();
	EnemyNameLabel->SetText(FText::FromString("Dayakci"));
}

void UCloseCombatHpUI::UpdateHp(float Health, float MaxHealth)
{
	HealthBar->SetPercent(Health / MaxHealth);
	CurrentHealthLabel->SetText(FText::AsNumber(Health));
}
