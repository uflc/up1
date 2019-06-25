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

	//�ൿ ����. �̿� ���� �ִϸ��̼��� ������.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ETDAnimState UnitState;

	UPROPERTY(BlueprintReadWrite)
	TArray<ETDAnimState> StatesQueue;

	UPROPERTY()
	int32 FlipbooksNum;

	void SetState(ETDAnimState InState);

	//������ �ִϸ��̼����� ������Ʈ. ���� �ִϸ��̼��� �����. See UPaperFlipbookComponent::SetFlipbook()
	virtual void UpdateAnimation();
	
public:
	virtual void InitializeComponent() override;

	void SetFlipbooks(const TArray<UPaperFlipbook*>& InFlipbooks, bool bShouldUpdate = true);

	bool SetFlipbookIndex(int32 Index);

	//�ൿ ���¸� �ٲٰ� ������ �ִϸ��̼����� ������Ʈ. See UpdateAnimation()
	UFUNCTION(BlueprintCallable)
	virtual void ChangeState(ETDAnimState InState, bool bShouldUpdate = true);

	UFUNCTION()
	virtual void ReceiveOnFinishedPlaying();

	//���� ���¿� �˸��� �ִϸ��̼��� ����.
	virtual int32 GetDesiredAnimationIndex();

	FORCEINLINE ETDAnimState GetState() const { return UnitState; }
	FORCEINLINE const TArray<UPaperFlipbook*>& GetFlipbooks() { return SourceFlipbooks; }
	FORCEINLINE int32 GetFlipbooksNum() const { return FlipbooksNum; }
};
