// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "TDTypes.h"

TOWERDEFENSE_API DECLARE_LOG_CATEGORY_EXTERN(LogTowerDefense, Log, All);

#define TD_LOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define TD_LOG_C(Verbosity) UE_LOG(LogTowerDefense, Verbosity, TEXT("%s"), *TD_LOG_CALLINFO)
#define TD_LOG(Verbosity, Format, ...) UE_LOG(LogTowerDefense, Verbosity, TEXT("%s %s"), *TD_LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__)) 