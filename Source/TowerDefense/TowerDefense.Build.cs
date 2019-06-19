// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class TowerDefense : ModuleRules
{
	public TowerDefense(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Paper2D", "AIModule", "NavigationSystem" });	

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        PrivateIncludePaths.AddRange
        (
            new string[]
            {
                "TowerDefense/Private/Unit",
                "TowerDefense/Private/Bullet",
                "TowerDefense/Private/UI",
                "TowerDefense/Private/AI"
            }
        );
    }
}
