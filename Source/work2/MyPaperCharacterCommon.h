// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "UObject/NoExportTypes.h"
//#include "PaperFlipbook.h"
//#include "MyPaperCharacter.h"
#include "MyPaperCharacterCommon.generated.h"

enum class  EUnitState : uint8;
class UPaperFlipbook;
/**
 * 
 */
UCLASS(BlueprintType)
class UMyPaperCharacterCommon : public UDataAsset// : public UObject
{
	GENERATED_BODY()
	
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
	UFUNCTION()
	void Initialize();

	UFUNCTION()
	void LoadFlipbooksDeffered();

};
//
//UCLASS(BlueprintType)
//class WORK2_API UTDUnitCommonsDataBase : public UDataAsset
//{
//	GENERATED_BODY()
//
//	friend class AMyUMGGameModeBase;
//
//	UPROPERTY(EditAnywhere)
//	TArray<UMyPaperCharacterCommon> TDUnitCommons;
//};
