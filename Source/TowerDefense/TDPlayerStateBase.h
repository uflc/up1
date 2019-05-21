//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "GameFramework/PlayerState.h"
////#include "Kismet\GameplayStatics.h"
//#include "TDPlayerStateBase.generated.h"
//
//
//UENUM(BlueprintType)
//enum class EValueType : uint8
//{
//	Coin		UMETA(DisplayName = "Coin"),
//	Life 		UMETA(DisplayName = "Life"),
//	Mana		UMETA(DisplayName = "Mana"),
//	HeroHP		UMETA(DisplayName = "HeroHP")
//};
//
///**
// * 
// */
//UCLASS()
//class TOWERDEFENSE_API ATDPlayerStateBase : public APlayerState
//{
//	GENERATED_BODY()
//	
//protected:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Property")
//	int32 Coin;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Property")
//	int32 Life;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Property")
//	int32 Mana;
//
//
//public:
//	//@TODO ºÐ¸®
//	UFUNCTION(BlueprintCallable)
//	void UpdateValue(int32 Value,EValueType Type);
//};
//
////#define PLAYER_EARN_COIN(x) UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPlayerState<ATDPlayerStateBase>()->UpdateValue(x,EValueType::Coin)