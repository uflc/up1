// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "HomingProjectile.generated.h"

UCLASS()
class TOWERDEFENSE_API AHomingProjectile : public AProjectileBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHomingProjectile();

protected:
	// Called when the game starts or when spawned
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		class ATDCharacter* Target;

	virtual void BeginPlay() override;

	FVector VelocityVec;

	float SplashRange;

	bool IsDirectable;

	FVector GetDistanceVecToTarget();

	virtual void CalcVelocityVec(const FVector& DirectionVec);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void Initialize(ATDCharacter* iTarget, int32 iDamage, bool iIsDirectable, float iSplashRange);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void BulletDestroy();

	UFUNCTION(BlueprintCallable)
	void BulletDestroy_Implementation();
};
