// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectAlice : ModuleRules
{
	public ProjectAlice(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		//bEnableUndefinedIdentifierWarnings = false;
	
		PublicIncludePaths.AddRange(new string[]
		{
			"ProjectAlice",
			"ProjectAlice/Core",
			"ProjectAlice/GameFeature",
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
