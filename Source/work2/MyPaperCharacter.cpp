// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPaperCharacter.h"

AMyPaperCharacter::AMyPaperCharacter()
{

}

void AMyPaperCharacter::UpdateAnimation()
{
	UPaperFlipbook* DesiredAnim = FlipbookMap.Find(UnitState)->Get();

	if (DesiredAnim)	GetSprite()->SetFlipbook(DesiredAnim);

	//GetCharacterMovement()->
}
