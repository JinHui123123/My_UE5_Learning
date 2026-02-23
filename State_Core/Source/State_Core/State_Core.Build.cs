// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class State_Core : ModuleRules
{
	public State_Core(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"State_Core",
			"State_Core/Variant_Platforming",
			"State_Core/Variant_Platforming/Animation",
			"State_Core/Variant_Combat",
			"State_Core/Variant_Combat/AI",
			"State_Core/Variant_Combat/Animation",
			"State_Core/Variant_Combat/Gameplay",
			"State_Core/Variant_Combat/Interfaces",
			"State_Core/Variant_Combat/UI",
			"State_Core/Variant_SideScrolling",
			"State_Core/Variant_SideScrolling/AI",
			"State_Core/Variant_SideScrolling/Gameplay",
			"State_Core/Variant_SideScrolling/Interfaces",
			"State_Core/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
