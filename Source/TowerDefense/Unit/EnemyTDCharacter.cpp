// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTDCharacter.h"
#include "TDPlayerController.h"


AEnemyTDCharacter::AEnemyTDCharacter()
{
	Team = EUnitTeam::Enemy;
}

void AEnemyTDCharacter::Die_Implementation()
{
	Super::Die_Implementation();

	GetWorld()->GetFirstPlayerController<ATDPlayerController>()->UpdateValue(Bounty, EValueType::Coin);
}

void AEnemyTDCharacter::Finish()
{
	GetWorld()->GetFirstPlayerController<ATDPlayerController>()->UpdateValue(-LifeDamage, EValueType::Life);

	Destroy();
}
