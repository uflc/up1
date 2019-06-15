// Fill out your copyright notice in the Description page of Project Settings.


#include "TDPaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "TowerDefense.h"


UTDPaperFlipbookComponent::UTDPaperFlipbookComponent()
{
	bWantsInitializeComponent = true;
}

void UTDPaperFlipbookComponent::SetState(ETDAnimState InState)
{
	UnitState = InState;
}

void UTDPaperFlipbookComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	OnFinishedPlaying.AddDynamic(this, &UTDPaperFlipbookComponent::ReceiveOnFinishedPlaying);
}

void UTDPaperFlipbookComponent::SetFlipbooks(const TArray<UPaperFlipbook*>& InFlipbooks, bool bShouldUpdate/* = true*/)
{
	if (SourceFlipbooks == InFlipbooks) return;

	FlipbooksNum = InFlipbooks.Num();

	SourceFlipbooks = InFlipbooks;

	if (bShouldUpdate)
	{
		UpdateAnimation();
	}
}

bool UTDPaperFlipbookComponent::SetFlipbookIndex(int32 Index)
{
	if (Index < FlipbooksNum)
	{
		return SetFlipbook(SourceFlipbooks[Index]);
	}
	return false;
}

void UTDPaperFlipbookComponent::ChangeState(ETDAnimState InState, bool bShouldUpdate/*=true*/)
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
		ETDAnimState NextState = ETDAnimState::Idle;
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
		case ETDAnimState::Running:
		case ETDAnimState::Idle:
			SetLooping(true);
			break;
		default:
			SetLooping(false);
			return;
		}
		//Play looping animation.
		PlayFromStart();
	}
}

int32 UTDPaperFlipbookComponent::GetDesiredAnimationIndex()
{
	return (int32) UnitState;
}
