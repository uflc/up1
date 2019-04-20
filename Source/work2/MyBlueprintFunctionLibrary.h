// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PaperSprite.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 * 
 �ҽ����� �ְ� BP�� ���� �Լ��� BP�� Ŀ�������� �߰��ϱ� ���� ���̺귯��.
 */
UCLASS()
class WORK2_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

		//��������Ʈ�� �ҽ� �ؽ��� ���� ��ȯ.
		UFUNCTION(BlueprintPure, Category = Custom)
		static FVector2D GetSourceSize(UPaperSprite* sprite);
};
