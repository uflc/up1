// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPaperCharacter.h"
#include "Runtime/Engine/Classes/Engine/AssetManager.h"



AMyPaperCharacter::AMyPaperCharacter()
{

}

bool AMyPaperCharacter::UpdateAnimation()
{
	UPaperFlipbook* DesiredAnim = FlipbookMap.Find(UnitState)->Get();

	if (DesiredAnim)
	{
		GetSprite()->SetFlipbook(DesiredAnim);
		return true;
	}
	else return false;

	//GetCharacterMovement()->
}

void AMyPaperCharacter::ChangeState(EUnitState InState)
{
	UnitState = InState;
	UpdateAnimation();
}

void AMyPaperCharacter::BeginPlay()
{
	Super::BeginPlay();

	
	auto& AssetLoader = UAssetManager::GetStreamableManager();

	TArray<FStringAssetReference> AssetsToLoad;
	for (auto it = FlipbookMap.begin(); it != FlipbookMap.end(); ++it)
	{
		AssetsToLoad.AddUnique(it.Value().ToStringReference());
	}
	AssetLoader.RequestAsyncLoad(AssetsToLoad, FStreamableDelegate::CreateUObject(this, &AMyPaperCharacter::FlipbooksDeffered));
}

void AMyPaperCharacter::FlipbooksDeffered()
{
	
	for (auto it = FlipbookMap.begin(); it != FlipbookMap.end(); ++it)
	{
		TAssetPtr<UPaperFlipbook> NewFlipbook = it.Value();
		if (NewFlipbook)		  NewFlipbook.Get();	
	}
}
