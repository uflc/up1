// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TowerDefense.h"
#include "PaperFlipbookComponent.h"
#include "TDTypes.h"
#include "TDPaperFlipbookComponent.generated.h"

/**
 * 
 */
UCLASS()
class UTDPaperFlipbookComponent : public UPaperFlipbookComponent
{
	GENERATED_BODY()
	
public:
	UTDPaperFlipbookComponent();

protected:
	UPROPERTY()
	TArray<UPaperFlipbook*> SourceFlipbooks;

	//행동 상태. 이에 따라 애니메이션이 결정됨.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ETDAnimState UnitState;

	UPROPERTY(BlueprintReadWrite)
	TArray<ETDAnimState> StatesQueue;

	UPROPERTY()
	int32 FlipbooksNum;

	void SetState(ETDAnimState InState);

	//적절한 애니메이션으로 업데이트. 루핑 애니메이션은 재생됨. See UPaperFlipbookComponent::SetFlipbook()
	virtual void UpdateAnimation();
	
public:
	virtual void InitializeComponent() override;

	void SetFlipbooks(const TArray<UPaperFlipbook*>& InFlipbooks, bool bShouldUpdate = true);

	bool SetFlipbookIndex(int32 Index);

	//행동 상태를 바꾸고 적절한 애니메이션으로 업데이트. See UpdateAnimation()
	UFUNCTION(BlueprintCallable)
	virtual void ChangeState(ETDAnimState InState, bool bShouldUpdate = true);

	UFUNCTION()
	virtual void ReceiveOnFinishedPlaying();

	//현재 상태에 알맞은 애니메이션을 구함.
	virtual int32 GetDesiredAnimationIndex();

	FORCEINLINE ETDAnimState GetState() const { return UnitState; }
	FORCEINLINE const TArray<UPaperFlipbook*>& GetFlipbooks() { return SourceFlipbooks; }
	FORCEINLINE int32 GetFlipbooksNum() const { return FlipbooksNum; }
};
