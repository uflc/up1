 // Fill out your copyright notice in the Description page of Project Settings.

#include "UITowerBase.h"
#include "CanvasPanel.h"
#include "CanvasPanelSlot.h"
#include "WidgetTree.h"
#include "UITowerButton.h"
#include "TextBlock.h"
#include "Tower.h"
#include "Runtime/UMG/Public/UMG.h"

bool UUITowerBase::SelectPreset(FString iName)
{
	// TODO :: Implement this
	bool rv=false;
	if(!Root->HasAnyChildren()) {
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, TEXT("NO CHILD__ROOT"));
	return false;}

	for(int idx=0;idx<=Root->GetChildrenCount()-1;idx++){

		auto Child = Root->GetChildAt(idx);
		UCanvasPanel* TowerDescription=nullptr;
		UCanvasPanel* TowerStatus = nullptr;
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, Child->GetName());
		auto canvasName = Child->GetName();
		if(canvasName.Equals(iName)){

			Child->SetIsEnabled(true); Child->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			rv=true;
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, TEXT("Find Matching One"));
		}
		else if(canvasName.Left(2).Equals("S_")) {
			Child->SetIsEnabled(true); Child->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

			if (canvasName.Contains("Status")){ TowerStatus=Cast<UCanvasPanel>(Child); }
			else if (canvasName.Contains("Description")){ TowerDescription= Cast<UCanvasPanel>(Child); }

		}
		else { 
			Child->SetIsEnabled(false); Child->SetVisibility(ESlateVisibility::Collapsed);
		}

		Cast<UTextBlock>(TowerStatus->GetChildAt(0))->SetText(FText::FromString(OwnTower->GetTowerStatusText()));
		Cast<UTextBlock>(TowerDescription->GetChildAt(0))->SetText(FText::FromString(OwnTower->GetTowerStatusText()));

	}
	return rv;
}

bool UUITowerBase::SetButtonsEvent()
{
	if (!Root->HasAnyChildren()) {
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, TEXT("NO CHILD__ROOT"));
		return false;
	}
	
	for (int idx = 0; idx <= Root->GetChildrenCount() - 1; idx++) {

		UCanvasPanel* ChildCanvas = Cast<UCanvasPanel>(Root->GetChildAt(idx));
		if(!ChildCanvas) continue;
		for (int idx2 = 0; idx2 <= ChildCanvas->GetChildrenCount() - 1; idx2++) {
			UUITowerButton* Button = Cast<UUITowerButton>(ChildCanvas->GetChildAt(idx2));
			if (!Button) continue;

			Button->OnClicked.AddDynamic(Button, &UUITowerButton::ButtonEvent);
			Button->OnClicked.AddDynamic(this, &UUITowerBase::CloseUI);
			Button->__native_SetRootCanvas(this);
		}
	}
	return true;
	
}

void UUITowerBase::CloseUI()
{
	for (int idx = 0; idx <= Root->GetChildrenCount() - 1; idx++) {
	auto Child = Root->GetChildAt(idx);
	Child->SetIsEnabled(false);
	Child->SetVisibility(ESlateVisibility::Collapsed);
	}
	OwnTower->ResetMaterial();
}

