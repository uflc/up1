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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	float Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	class ATDCharacter* Target;

	UPROPERTY(Category = Unit, VisibleAnywhere, BlueprintReadOnly)
	class UPaperFlipbookComponent* Animation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	bool IsDirectable;
public:	
	//UFUNCTION(BlueprintCallable)
	void SetTarget(ATDCharacter* iTarget);

	void SetCommonData(UTDProjectileCommonData* iData);

	virtual void Initialize();

	//UFUNCTION(BlueprintCallable)
	virtual void BulletDestroy();
};
