// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/TDPaperFlipbookComponent.h"
#include "DirTDPaperFlipbookComponent.generated.h"

/**
 * 
 */
UCLASS()
class UDirTDPaperFlipbookComponent : public UTDPaperFlipbookComponent
{
	GENERATED_BODY()
	
protected:
	//�ٶ󺸴� ����. �̿� ���� �ִϸ��̼��� ������.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EDirection Direction;

public:
	UFUNCTION(BlueprintCallable)
	virtual void FaceTo(AActor* Target);

	UFUNCTION(BlueprintCallable)
	void FaceToAggroTarget();

	virtual int32 GetDesiredAnimationIndex() override;

};
