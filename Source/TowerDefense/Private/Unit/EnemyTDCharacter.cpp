// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTDCharacter.h"
#include "EnemyTDCharAIController.h"
#include "TDPlayerController.h"

AEnemyTDCharacter::AEnemyTDCharacter()
{
	Team = EUnitTeam::Enemy;

	AIControllerClass = AEnemyTDCharAIController::StaticClass();
}

void AEnemyTDCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SetActorEnableCollision(false);
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
