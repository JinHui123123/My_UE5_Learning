// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Learn_VS : ModuleRules
{
	public Learn_VS(ReadOnlyTargetRules Target) : base(Target)
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
			"Learn_VS",
			"Learn_VS/Variant_Platforming",
			"Learn_VS/Variant_Platforming/Animation",
			"Learn_VS/Variant_Combat",
			"Learn_VS/Variant_Combat/AI",
			"Learn_VS/Variant_Combat/Animation",
			"Learn_VS/Variant_Combat/Gameplay",
			"Learn_VS/Variant_Combat/Interfaces",
			"Learn_VS/Variant_Combat/UI",
			"Learn_VS/Variant_SideScrolling",
			"Learn_VS/Variant_SideScrolling/AI",
			"Learn_VS/Variant_SideScrolling/Gameplay",
			"Learn_VS/Variant_SideScrolling/Interfaces",
			"Learn_VS/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
