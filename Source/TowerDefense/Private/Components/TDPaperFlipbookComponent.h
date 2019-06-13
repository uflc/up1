// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookComponent.h"
#include "TDTypes.h"
#include "TDPaperFlipbookComponent.generated.h"

/**
 * 
 */
UCLASS(EditInlineNew)
class UTDPaperFlipbookComponent : public UPaperFlipbookComponent
{
	GENERATED_BODY()
	
protected:
	/*UPROPERTY()
	class UTDUnitCommonData* UnitData;*/

	UPROPERTY()
	TArray<UPaperFlipbook*> SourceFlipbooks;

	//행동 상태. 이에 따라 애니메이션이 결정됨.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EUnitState UnitState;

	UPROPERTY()
	int32 MaxState;

	void SetState(EUnitState InState);
	
public:
	//virtual void SetUnitData(UTDUnitCommonData* InData);

	void SetFlipbooks(const TArray<UPaperFlipbook*>& InFlipbooks, EUnitState InitialState = EUnitState::Idle, int32 InMaxState = 0);

	//행동 상태를 바꾸고 적절한 애니메이션으로 업데이트. See UpdateAnimation()
	UFUNCTION(BlueprintCallable)
	virtual void ChangeState(EUnitState InState);

	//적절한 애니메이션으로 업데이트. 루핑 애니메이션은 재생됨. See UPaperFlipbookComponent::SetFlipbook()
	virtual void UpdateAnimation();

	//현재 상태에 알맞은 애니메이션을 구함.
	virtual UPaperFlipbook* GetDesiredAnimation();
};
