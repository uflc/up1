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

	//�ൿ ����. �̿� ���� �ִϸ��̼��� ������.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EUnitState UnitState;

	UPROPERTY()
	int32 MaxState;

	void SetState(EUnitState InState);
	
public:
	//virtual void SetUnitData(UTDUnitCommonData* InData);

	void SetFlipbooks(const TArray<UPaperFlipbook*>& InFlipbooks, EUnitState InitialState = EUnitState::Idle, int32 InMaxState = 0);

	//�ൿ ���¸� �ٲٰ� ������ �ִϸ��̼����� ������Ʈ. See UpdateAnimation()
	UFUNCTION(BlueprintCallable)
	virtual void ChangeState(EUnitState InState);

	//������ �ִϸ��̼����� ������Ʈ. ���� �ִϸ��̼��� �����. See UPaperFlipbookComponent::SetFlipbook()
	virtual void UpdateAnimation();

	//���� ���¿� �˸��� �ִϸ��̼��� ����.
	virtual UPaperFlipbook* GetDesiredAnimation();
};
