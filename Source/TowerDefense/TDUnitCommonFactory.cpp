// Fill out your copyright notice in the Description page of Project Settings.


#include "TDUnitCommonFactory.h"

#include "TDUnitCommonData.h"


UTDUnitCommonFactory::UTDUnitCommonFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = UTDUnitCommonData::StaticClass();
	bCreateNew = false;
	bEditorImport = true;
}
