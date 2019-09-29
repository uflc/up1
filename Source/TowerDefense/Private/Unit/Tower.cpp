// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "TowerDataTree.h"
#include "TDPlayerController.h"
#include "TDAIController.h"
#include "PaperFlipbook.h"
#include "Components/TDPaperFlipbookComponent.h"
#include "PaperSpriteComponent.h"
#include "WeaponComponent.h"
#include "NavArea_Null.h"
#include "ProfTowerData.h"
#include "PassiveSkillComponent.h"

ATower::ATower()
{
	InitializeDefaults();
}

ATower::ATower(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	InitializeDefaults();
}

void ATower::InitializeDefaults()
{
	static const FVector BoxExtent(137.5f, 100.0f, 5.0f);
	Box->InitBoxExtent(BoxExtent);
	Box->bDynamicObstacle = true;
	Box->AreaClass = UNavArea_Null::StaticClass();

	static FName VisibiltyProfileName(TEXT("UI"));
	Animation->SetCollisionProfileName(VisibiltyProfileName);
	Animation->SetRelativeLocation(FVector(0.0f, -150.0f, 0.0f));

	if (Shadow)
	{
		Shadow->SetRelativeLocation(FVector(0.0f, -0.1f, -240.0f));
	}

	Team = EUnitTeam::Player;
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
}

void ATower::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	const UTowerData* TowerData = Cast<UTowerData>(UnitData);

	if (TowerData)
	{
		TotalCost = TowerData->GetCost();
	}
}

void ATower::OnDeselected()
{
	bIsSelected = false;
}

void ATower::ShowActionMenu()
{
	GetWorld()->GetFirstPlayerController<ATDPlayerController>()->ShowTowerActionMenu(this);
}

int32 ATower::GetTalentLevel(const ETowerType & UpType) const
{
	return TalentLevel[(uint8)UpType];
}

float ATower::GetTowerRange_Implementation()
{
	return GetAttackRange();
}

bool ATower::Upgrade_Implementation(ETowerType UpType)
{
	UTowerData* TowerData = Cast<UTowerData>(UnitData);
	if (!TowerData) return false;

	UTowerData* Upgraded = TowerData->GetNextUpgraded(UpType);
	if (!Upgraded) return false;

	UnitData = Upgraded;
	TotalCost += Upgraded->GetCost();

	ApplyData();

	return true;
}

bool ATower::UpgradeTalent_Implementation(ETowerType UpType)
{
	UProfTowerData* ProfTowerData = Cast<UProfTowerData>(UnitData);
	if (!ProfTowerData) return false;

	int32& CurTalentLevel = TalentLevel[(uint8)UpType];

	if (CurTalentLevel >= TALENT_LEVEL_MAX) return false;

	FTalentInfo TalentInfo = ProfTowerData->GetTalentInfo(UpType);
	UDataAsset* TalentData = TalentInfo.TalentData[CurTalentLevel];
	TSubclassOf<UActorComponent> TalentClass = TalentInfo.Class;
	bool DupChecker = false;

	switch (TalentInfo.ClassType)
	{
	case ETalentType::ActiveSkill:
		for (auto iSkillComp : SkillCompArr)
		{
			if (iSkillComp->StaticClass() == TalentInfo.Class.Get())
			{
				iSkillComp->SetCommonData((UTDWeaponCommonData*)TalentData);
				DupChecker = true;
				break;
			}
		}
		if (!DupChecker)
		{
			UWeaponComponent* NewComp = NewObject<UWeaponComponent>(this, TalentInfo.Class.Get());
			NewComp->SetCommonData((UTDWeaponCommonData*)TalentData);
			SkillCompArr.Add(NewComp);
		}
		break;

	case ETalentType::PassiveSkill:
		for (auto iPassiveComp : PassiveCompArr)
		{
			if (iPassiveComp->StaticClass() == TalentInfo.Class.Get())
			{
				iPassiveComp->SetCommonData((UPassiveCommonData*)TalentData);
				DupChecker=true;
				break;
			}
		}
		if (!DupChecker)
		{
			AddPassiveSkill(TalentInfo.Class.Get(), (UPassiveCommonData*)TalentData);
			//UPassiveSkillComponent* NewComp = NewObject<UPassiveSkillComponent>(this, TalentInfo.Class.Get());
			//NewComp->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
			//NewComp->RegisterComponent();
			//NewComp->SetCommonData((UPassiveCommonData*)TalentData);
			//NewComp->Initialize();
			//PassiveCompArr.Add(NewComp);
		}
		break;

	case ETalentType::Weapon:
		WeaponComp->SetCommonData((UTDWeaponCommonData*)TalentData);
		break;

	default:
		break;
	}

	CurTalentLevel++;

	//Don't need with talent
	//TotalCost += Upgraded->GetCost();

	return true;
}

void ATower::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);

	TD_LOG_C(Warning);//

	if (bIsSelected) return;

	bIsSelected = true;
	ShowActionMenu();
}
