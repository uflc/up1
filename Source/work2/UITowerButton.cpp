// Fill out your copyright notice in the Description page of Project Settings.

#include "UITowerButton.h"
#include "UITowerBase.h"
#include "Tower.h"

void UUITowerButton::ButtonEvent()
{
	FString Name=this->GetName();
	RootWidget->__native_GetOwnTower()->ResponseButtonEvent(FCString::Atoi(*Name.Right(1)));
}
