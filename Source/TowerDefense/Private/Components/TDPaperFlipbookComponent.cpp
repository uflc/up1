// Fill out your copyright notice in the Description page of Project Settings.


#include "TDPaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "TDUnitCommonData.h"
#include "TowerDefense.h"

void UTDPaperFlipbookComponent::SetState(EUnitState InState)
{
	UnitState = InState;
}

void UTDPaperFlipbookComponent::SetFlipbooks(const TArray<UPaperFlipbook*>& InFlipbooks, EUnitState InitialState, int32 InMaxState)
{
	if (!InFlipbooks.Num() == 0)
	{
		SourceFlipbooks = InFlipbooks;
	}

	if (InMaxState <= 0 ||InMaxState > SourceFlipbooks.Num())
	{
		MaxState = SourceFlipbooks.Num();
	}
	else
	{
		MaxState = InMaxState;
	}

	ChangeState(InitialState);
}

void UTDPaperFlipbookComponent::ChangeState(EUnitState InState)
{
	if (UnitState == InState) return;

	SetState(InState);
	UpdateAnimation();
}

void UTDPaperFlipbookComponent::UpdateAnimation()
{
	if (SetFlipbook(GetDesiredAnimation()))
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

UPaperFlipbook* UTDPaperFlipbookComponent::GetDesiredAnimation()
{
	if (MaxState == 0) return nullptr;

	return SourceFlipbooks[(int32) UnitState];
}
