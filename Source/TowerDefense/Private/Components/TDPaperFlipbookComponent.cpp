// Fill out your copyright notice in the Description page of Project Settings.


#include "TDPaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "TowerDefense.h"


UTDPaperFlipbookComponent::UTDPaperFlipbookComponent()
{
	bWantsInitializeComponent = true;
}

void UTDPaperFlipbookComponent::SetState(EUnitState InState)
{
	UnitState = InState;
}

void UTDPaperFlipbookComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	OnFinishedPlaying.AddDynamic(this, &UTDPaperFlipbookComponent::ReceiveOnFinishedPlaying);
}

void UTDPaperFlipbookComponent::SetFlipbooks(const TArray<UPaperFlipbook*>& InFlipbooks, EUnitState InitialState)
{
	if (SourceFlipbooks == InFlipbooks) return;

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
	SetState(InState);

	if (bShouldUpdate)
	{
		UpdateAnimation();
	}
}

void UTDPaperFlipbookComponent::ReceiveOnFinishedPlaying()
{
	if (StatesQueue.Num() != 0)
	{
		EUnitState NextState = EUnitState::Idle;
		StatesQueue.HeapPop(NextState);
		ChangeState(NextState);
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
