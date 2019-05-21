// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleFlipbookEffect.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
//#include "TimerManager.h"

void ASimpleFlipbookEffect::SetupEffect(UPaperFlipbook* inFlipbook) {

	if(!inFlipbook) {Destroy();return;}

	auto FlipbookComp = GetRenderComponent();
	FlipbookComp->SetFlipbook(inFlipbook);
	FlipbookComp->SetLooping(false);
	FlipbookComp->PlayFromStart();
	SetLifeSpan(inFlipbook->GetTotalDuration());
}