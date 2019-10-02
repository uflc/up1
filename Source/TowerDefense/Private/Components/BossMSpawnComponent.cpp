// Fill out your copyright notice in the Description page of Project Settings.


#include "BossMSpawnComponent.h"

void UBossMSpawnComponent::UseWeapon()
{
	Super::UseWeapon();

	Spawn();
}
