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
	UPROPERTY()
	TArray<UPaperFlipbook*> SourceFlipbooks;

	//�ൿ ����. �̿� ���� �ִϸ��̼��� ������.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EUnitState UnitState;

	UPROPERTY()
	int32 FlipbooksNum;

	void SetState(EUnitState InState);

	//������ �ִϸ��̼����� ������Ʈ. ���� �ִϸ��̼��� �����. See UPaperFlipbookComponent::SetFlipbook()
	virtual void UpdateAnimation();
	
public:

	void SetFlipbooks(const TArray<UPaperFlipbook*>& InFlipbooks, EUnitState InitialState = EUnitState::Idle);

	bool SetFlipbookIndex(int32 Index);

	//�ൿ ���¸� �ٲٰ� ������ �ִϸ��̼����� ������Ʈ. See UpdateAnimation()
	UFUNCTION(BlueprintCallable)
	virtual void ChangeState(EUnitState InState, bool bShouldUpdate = true);

	//���� ���¿� �˸��� �ִϸ��̼��� ����.
	virtual int32 GetDesiredAnimationIndex();

	FORCEINLINE EUnitState GetState() const { return UnitState; }
	FORCEINLINE const TArray<UPaperFlipbook*>& GetFlipbooks() { return SourceFlipbooks; }
	FORCEINLINE int32 GetFlipbooksNum() const { return FlipbooksNum; }
};
