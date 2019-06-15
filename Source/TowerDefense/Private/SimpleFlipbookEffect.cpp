// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleFlipbookEffect.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"

void ASimpleFlipbookEffect::SetupEffect(UPaperFlipbook* InFlipbook) 
{
	if (!InFlipbook) 
	{
		Destroy();
		return;
	}

	UPaperFlipbookComponent* FlipbookComp = GetRenderComponent();

	FlipbookComp->SetRelativeRotation(FRotator(0,0,-90.0f));
	FlipbookComp->AddLocalOffset(FVector(0,0,0.5f));
	FlipbookComp->SetFlipbook(InFlipbook);
	FlipbookComp->SetLooping(false);

	SetLifeSpan(InFlipbook->GetTotalDuration());
}
