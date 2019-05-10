// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyPaperCharacterCommon.generated.h"

enum class  EUnitState : uint8;
class UPaperFlipbook;

/**
 * 
 TDUnit 종류별로 공통된 정보를 하나의 데이터어셋에 담고 유닛들은 공유.
 BluePrint Class -> DataAsset -> MyPaperCharacterCommon을 선택해서 생성.
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
