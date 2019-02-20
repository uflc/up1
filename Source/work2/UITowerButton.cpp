// Fill out your copyright notice in the Description page of Project Settings.

#include "UITowerButton.h"
#include "UITowerBase.h"
#include "Tower.h"
#include "Engine.h"

void UUITowerButton::ButtonEvent()
{
	FString Name=this->GetName();
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, Name);
	RootWidget->__native_GetOwnTower()->ResponseButtonEvent(FCString::Atoi(*Name.Right(1)));
}
