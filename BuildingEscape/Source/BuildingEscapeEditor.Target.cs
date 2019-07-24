// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class BuildingEscapeEditorTarget : TargetRules
{
	public BuildingEscapeEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "BuildingEscape" } );

		// Added in L70, allows to show errors related to missing *.h files.
		// bUseUnityBuild = false;
	 	// bUsePCHFiles = false;
	}
}
