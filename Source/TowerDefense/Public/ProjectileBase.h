// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

UCLASS(Abstract)
class TOWERDEFENSE_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	UPROPERTY(Category = Unit, VisibleAnywhere, BlueprintReadOnly)
	class UTDProjectileCommonData* ProjectileCommon;

	UPROPERTY(Category = Unit,EditAnywhere, BlueprintReadWrite)
	float Velocity = 0;

	UPROPERTY(Category = Unit,EditAnywhere, BlueprintReadWrite)
	class ATDCharacter* Target;

	UPROPERTY(Category = Unit, VisibleAnywhere, BlueprintReadOnly)
	class UPaperFlipbookComponent* Animation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDirectable=false;
public:	
	//UFUNCTION(BlueprintCallable)
	void SetTarget(ATDCharacter* InTarget);

	void SetCommonData(UTDProjectileCommonData* InData);

	virtual void Initialize();

	//UFUNCTION(BlueprintCallable)
	virtual void BulletDestroy();
};
