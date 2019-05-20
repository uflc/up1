// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Engine.h"
#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(TowerDefense, Log, All);

#define TD_LOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define TD_LOG_CALLONLY(Verbosity) UE_LOG(TowerDefense, Verbosity, TEXT("%s"), *TD_LOG_CALLINFO)
#define TD_LOG(Verbosity, Format, ...) UE_LOG(TowerDefense, Verbosity, TEXT("%s %s"), *TD_LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__)) 