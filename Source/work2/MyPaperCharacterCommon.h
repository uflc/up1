// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyPaperCharacterCommon.generated.h"

enum class  EUnitState : uint8;
class UPaperFlipbook;

/**
 * 
 TDUnit �������� ����� ������ �ϳ��� �����;�¿� ��� ���ֵ��� ����.
 BluePrint Class -> DataAsset -> MyPaperCharacterCommon�� �����ؼ� ����.
 */
UCLASS(BlueprintType)
class UMyPaperCharacterCommon : public UDataAsset
{
	GENERATED_BODY()

	DECLARE_DELEGATE(FLoadCompletedSignature);

protected:
	friend class AMyPaperCharacter;
	friend class AMyUMGGameModeBase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TMap<EUnitState, TSoftObjectPtr<UPaperFlipbook>> FlipbookMap;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	float DefaultAttackRange;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	float DefaultAggroDrawnRange;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDUnit|Property")
	float DefaultDrawingAggroRange;

public:
	FLoadCompletedSignature OnFlipbooksLoaded;

	UFUNCTION()
	void Initialize();

	UFUNCTION()
	void LoadFlipbooksDeffered();

};
