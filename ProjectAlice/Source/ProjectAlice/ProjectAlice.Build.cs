// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectAlice : ModuleRules
{
	public ProjectAlice(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		//bEnableUndefinedIdentifierWarnings = false;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"ProjectAlice",
        });

		PrivateDependencyModuleNames.AddRange(new string[]
		{  
			"Core",
			"CoreUObject",
			"Engine",
			"EngineSettings",

			"UMG",
			"Slate",
			"SlateCore",

			"Niagara",

			"LevelSequence",
			"MovieScene",

			"GameplayTasks",

			"NavigationSystem",

			"AIModule",

			"InputCore",

			"OnlineSubsystem",
		});
	}
}
