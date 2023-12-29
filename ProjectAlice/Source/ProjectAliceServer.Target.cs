// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectAliceServerTarget : TargetRules
{
	public ProjectAliceServerTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "ProjectAlice" } );
	}
}
