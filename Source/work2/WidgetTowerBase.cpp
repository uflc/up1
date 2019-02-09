// Fill out your copyright notice in the Description page of Project Settings.

#include "WidgetTowerBase.h"
#include "CanvasPanel.h"
#include "CanvasPanelSlot.h"
#include "WidgetTree.h"
#include "Runtime/UMG/Public/UMG.h"

bool UWidgetTowerBase::SelectPreset(FString iName)
{
	// TODO :: Implement this
	bool rv=false;
	if(!Root->HasAnyChildren()) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, TEXT("NOCHILD"));
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