// Fill out your copyright notice in the Description page of Project Settings.


#include "TDPaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "TowerDefense.h"

void UTDPaperFlipbookComponent::SetState(EUnitState InState)
{
	UnitState = InState;
}

void UTDPaperFlipbookComponent::SetFlipbooks(const TArray<UPaperFlipbook*>& InFlipbooks, EUnitState InitialState)
{
	FlipbooksNum = InFlipbooks.Num();
	SourceFlipbooks = InFlipbooks;
	
	ChangeState(InitialState);
}

bool UTDPaperFlipbookComponent::SetFlipbookIndex(int32 Index)
{
	if (Index < FlipbooksNum)
	{
		return SetFlipbook(SourceFlipbooks[Index]);
	}
	return false;
}

void UTDPaperFlipbookComponent::ChangeState(EUnitState InState, bool bShouldUpdate)
{
	if (UnitState == InState) return;

	SetState(InState);

	if (bShouldUpdate)
	{
		UpdateAnimation();
	}
}

void UTDPaperFlipbookComponent::UpdateAnimation()
{
	if (SetFlipbookIndex(GetDesiredAnimationIndex()))
	{
		switch (UnitState)
		{
		case EUnitState::Running:
		case EUnitState::Idle:
			SetLooping(true);
			break;
		default:
			SetLooping(false);
			return;
		}

		PlayFromStart();
	}
}

int32 UTDPaperFlipbookComponent::GetDesiredAnimationIndex()
{
	return (int32) UnitState;
}
