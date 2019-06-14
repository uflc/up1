// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	EUnitState UnitState;

	UPROPERTY(BlueprintReadWrite)
	TArray<EUnitState> StatesQueue;

	UPROPERTY()
	int32 FlipbooksNum;

	void SetState(EUnitState InState);

	//������ �ִϸ��̼����� ������Ʈ. ���� �ִϸ��̼��� �����. See UPaperFlipbookComponent::SetFlipbook()
	virtual void UpdateAnimation();
	
public:
	virtual void InitializeComponent() override;

	void SetFlipbooks(const TArray<UPaperFlipbook*>& InFlipbooks, EUnitState InitialState = EUnitState::Idle);

	bool SetFlipbookIndex(int32 Index);

	//�ൿ ���¸� �ٲٰ� ������ �ִϸ��̼����� ������Ʈ. See UpdateAnimation()
	UFUNCTION(BlueprintCallable)
	virtual void ChangeState(EUnitState InState, bool bShouldUpdate = true);

	UFUNCTION()
	virtual void ReceiveOnFinishedPlaying();

	//���� ���¿� �˸��� �ִϸ��̼��� ����.
	virtual int32 GetDesiredAnimationIndex();

	FORCEINLINE EUnitState GetState() const { return UnitState; }
	FORCEINLINE const TArray<UPaperFlipbook*>& GetFlipbooks() { return SourceFlipbooks; }
	FORCEINLINE int32 GetFlipbooksNum() const { return FlipbooksNum; }
};
