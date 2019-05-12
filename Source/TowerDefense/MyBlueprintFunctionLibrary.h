// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDPlayerStateBase.h"
#include "PaperSprite.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 * 
 BP�� Ŀ�������� �߰��ϱ� ���� ���̺귯��.
 */
UCLASS()
class TOWERDEFENSE_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	//��������Ʈ�� �ؽ��� ����.
	UFUNCTION(BlueprintPure, Category = Custom)
	static FVector2D GetSourceSize(UPaperSprite* sprite);

	UFUNCTION(BlueprintCallable, Category = Custom)
	static void EarnCoin(UObject* CalledObj,int32 Value);

	UFUNCTION(BlueprintCallable, Category = Custom) 
	static void UpdateCurrentPlayerStateValue(UObject* CalledObj, int32 i,EValueType Type);
};