// Fill out your copyright notice in the Description page of Project Settings.


#include "TDCharWidget.h"
#include "TDCharacter.h"

void UTDCharWidget::SetOwner(ATDCharacter* NewOwner)
{
	if (Owner == NewOwner) return;

	Owner = NewOwner;

	PostSetOwner();
}
