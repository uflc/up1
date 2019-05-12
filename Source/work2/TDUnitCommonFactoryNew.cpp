// Fill out your copyright notice in the Description page of Project Settings.


#include "TDUnitCommonFactoryNew.h"

#include "TDUnitCommonData.h"

UTDUnitCommonFactoryNew::UTDUnitCommonFactoryNew(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SupportedClass = UTDUnitCommonData::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}


UObject * UTDUnitCommonFactoryNew::FactoryCreateNew(UClass * InClass, UObject * InParent, FName InName, EObjectFlags Flags, UObject * Context, FFeedbackContext * Warn)
{
	return NewObject<UTDUnitCommonData>(InParent, InClass, InName, Flags);
}

bool UTDUnitCommonFactoryNew::ShouldShowInNewMenu() const
{
	return true;
}
