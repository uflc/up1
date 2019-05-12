// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class TowerDefenseEditor : ModuleRules
{
	public TowerDefenseEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;


        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine",});

        PublicDependencyModuleNames.AddRange(new string[] { "TowerDefense" });


        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "UnrealEd" });


        PrivateIncludePaths.AddRange
        (
            new string[]
            {
                "TowerDefenseEditor/Private",
            }
        );

    }
}
