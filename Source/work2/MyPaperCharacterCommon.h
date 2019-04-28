// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyPaperCharacterCommon.generated.h"

enum class  EUnitState : uint8;
class UPaperFlipbook;
/**
 * 
 */
UCLASS(BluePrintable)
class WORK2_API UMyPaperCharacterCommon : public UObject
{
	GENERATED_BODY()
		//		/*UPROPERTY(Config)
		//		TArray<FStringAssetReference> UnitFlipbooks;*/
	protected:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
			TMap<EUnitState, TAssetPtr<UPaperFlipbook>> FlipbookMap;
		
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Property")
			float  DefaultAttackRange;
		
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Property")
			float DefaultAggroDrawnRange;
		
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Property")
			float DefaultDrawingAggroRange;

};
