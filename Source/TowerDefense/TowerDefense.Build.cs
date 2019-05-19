// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class TowerDefense : ModuleRules
{
	public TowerDefense(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Paper2D", "AIModule" });	

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        PrivateIncludePaths.AddRange
        (
            new string[]
            {
                "TowerDefense/Unit",
                "TowerDefense/Bullet",
                "TowerDefense/UI"
            }
        );

    }
}
