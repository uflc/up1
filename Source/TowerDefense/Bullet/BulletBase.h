// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDCharacter.h"
#include "BulletBase.generated.h"

UCLASS()
class TOWERDEFENSE_API ABulletBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	ATDCharacter* Target;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	float Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	int32 Damage;

	bool IsDirectable;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void Initialize(ATDCharacter* iTarget, int32 iDamage, bool iIsDirectable);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void BulletDestroy();

	UFUNCTION(BlueprintCallable)
	void BulletDestroy_Implementation();
};
