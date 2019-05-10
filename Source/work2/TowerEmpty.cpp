// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerEmpty.h"
#include "TowerArcher.h"
#include "UITowerBase.h"
#include "MyUMGGameModeBase.h"
#include "Engine.h"

ATowerEmpty::ATowerEmpty()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

inline FString ATowerEmpty::GetPresetName()
{
	return "Empty";
}

FString ATowerEmpty::GetTowerStatusText()
{
	return "TowerEmpty Status Test";
}

FString ATowerEmpty::GetTowerDescriptionText()
{
	return "TowerEmpty Description Test";
}