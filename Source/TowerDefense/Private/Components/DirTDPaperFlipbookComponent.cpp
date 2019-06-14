// Fill out your copyright notice in the Description page of Project Settings.


#include "DirTDPaperFlipbookComponent.h"
#include "TDAIController.h"


int32 UDirTDPaperFlipbookComponent::GetDesiredAnimationIndex()
{
	return (int32) Direction * 2 + Super::GetDesiredAnimationIndex();
}

void UDirTDPaperFlipbookComponent::FaceTo(AActor* Target)
{
	if (!Target) return;

	const EDirection OldDirection = Direction;
	const FVector DirToTarget = Target->GetActorLocation() - GetOwner()->GetActorLocation();
	Direction = DirToTarget.X > 0 ? DirToTarget.Y > 0 ? EDirection::RD : EDirection::RT
		                          : DirToTarget.Y > 0 ? EDirection::LD : EDirection::LT;
	if (OldDirection != Direction)
	{
		UpdateAnimation();
	}
}

void UDirTDPaperFlipbookComponent::FaceToAggroTarget()
{
	ATDAIController* Controller = Cast<ATDAIController>(Cast<APawn>(GetOwner())->GetController());
	if (!Controller) return;

	FaceTo(Controller->GetAggroTarget());
}