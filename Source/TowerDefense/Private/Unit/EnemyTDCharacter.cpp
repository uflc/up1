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

	//웨이브에서 스폰된 후(목적지 분기가 정해진 후)에 true로 설정. 이후, 레벨에 존재하는 트리거들이 발동될 것.
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
