// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyPaperCharacter.h"
#include "BulletBase.generated.h"

UCLASS()
class WORK2_API ABulletBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	AMyPaperCharacter* Target;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	float Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	int32 Damage;

	bool IsDirectable;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void Initialize(AMyPaperCharacter* iTarget, int32 iDamage, bool iIsDirectable);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void BulletDestroy();

	UFUNCTION(BlueprintCallable)
	void BulletDestroy_Implementation();
};
