// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BulletBase.h"
#include "ParabolicBullet.generated.h"


class AMyPaperCharacter;
/**
 * 
 */
UCLASS()
class WORK2_API AParabolicBullet : public ABulletBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector VelocityVec;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurveScale;

	float Counter;

	float StartingVelocityPercent;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void BulletDestroy();

	void BulletDestroy_Implementation();

	virtual void Initialize(AMyPaperCharacter* iTarget,int32 iDamage);
};
