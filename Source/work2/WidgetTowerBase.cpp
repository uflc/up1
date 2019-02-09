// Fill out your copyright notice in the Description page of Project Settings.

#include "WidgetTowerBase.h"
#include "CanvasPanel.h"
#include "CanvasPanelSlot.h"
#include "WidgetTree.h"
#include "Runtime/UMG/Public/UMG.h"

void UWidgetTowerBase::NativeConstruct()
{
	Super::NativeConstruct();
}

TSharedRef<SWidget> UWidgetTowerBase::RebuildWidget()
{
	if (WidgetTree)
	{
		Root = Cast<UCanvasPanel>(GetRootWidget());
		if (Root == nullptr)
		{
			Root = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), FName("Root"));

			UCanvasPanelSlot * RootSlot = Cast<UCanvasPanelSlot>(Root->Slot);
			if (RootSlot)
			{
				RootSlot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
				RootSlot->SetOffsets(FMargin(0.f, 0.f));
			}
			WidgetTree->RootWidget = Root;
		}
	}
	Root->bIsVariable = true;
	TSharedRef<SWidget> Widget = Super::RebuildWidget();

	return Widget;
}

bool UWidgetTowerBase::SelectPreset(FString iName)
{
	// TODO :: Implement this
	bool rv=false;
	if(!Root->HasAnyChildren()) return false;

	for(int idx=0;idx<=Root->GetChildrenCount()-1;idx++){

		auto Child = Root->GetChildAt(idx);

		if(Child->GetName().Equals(iName)){ 
			Child->SetIsEnabled(true); Child->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			rv=true;
		}
		else { 
			Child->SetIsEnabled(false); Child->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	return rv;
}

void UWidgetTowerBase::AddChildtoRootCanvas(UWidget* iWidget)
{
	Root->AddChildToCanvas(iWidget);
}
