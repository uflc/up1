// Fill out your copyright notice in the Description page of Project Settings.

#include "UITowerBase.h"
#include "CanvasPanel.h"
#include "CanvasPanelSlot.h"
#include "WidgetTree.h"
#include "UITowerButton.h"
#include "Runtime/UMG/Public/UMG.h"

bool UUITowerBase::SelectPreset(FString iName)
{
	// TODO :: Implement this
	bool rv=false;
	if(!Root->HasAnyChildren()) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, TEXT("NO CHILD__ROOT"));
	return false;}

	for(int idx=0;idx<=Root->GetChildrenCount()-1;idx++){

		auto Child = Root->GetChildAt(idx);

		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, Child->GetName());

		if(Child->GetName().Equals(iName)){ 

			Child->SetIsEnabled(true); Child->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			rv=true;
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, TEXT("Find Matching One"));
		}
		else { 
			Child->SetIsEnabled(false); Child->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	return rv;
}

bool UUITowerBase::SetButtonsEvent()
{
	if (!Root->HasAnyChildren()) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, TEXT("NO CHILD__ROOT"));
		return false;
	}
	
	for (int idx = 0; idx <= Root->GetChildrenCount() - 1; idx++) {

		UCanvasPanel* ChildCanvas = Cast<UCanvasPanel>(Root->GetChildAt(idx));
		if(!ChildCanvas) continue;
		for (int idx2 = 0; idx2 <= ChildCanvas->GetChildrenCount() - 1; idx2++) {

			if (idx2 == 0) {
				UUITowerButton* Button = Cast<UUITowerButton>(ChildCanvas->GetChildAt(idx2));
				Button->OnClicked.AddDynamic(Button, &UUITowerButton::ButtonEvent);
				Button->__native_SetRootCanvas(this);
			}
			else{
				UButton* Button = Cast<UButton>(ChildCanvas->GetChildAt(idx2));
			
				if (!Button) continue;
				Button->OnClicked.AddDynamic(this,&UUITowerBase::DelegateButtonEvent);
			}
		}
	}
	return true;
	
}


void UUITowerBase::DelegateButtonEvent()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, TEXT("Button Clicked"));

}