// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleFlipbookEffect.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
//#include "TimerManager.h"

void ASimpleFlipbookEffect::SetupEffect(UPaperFlipbook* inFlipbook) {
	auto comp = GetRenderComponent();
	comp->SetFlipbook(inFlipbook);
	comp->SetLooping(false);
	comp->PlayFromStart();

	FTimerHandle handle;
	GetWorldTimerManager().SetTimer(handle,[this](){
	Destroy();
	}, inFlipbook->GetTotalDuration(),false);
}