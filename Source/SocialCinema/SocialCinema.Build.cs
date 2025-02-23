// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class SocialCinema : ModuleRules
{
	public SocialCinema(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

        PublicDependencyModuleNames.Add("Blu");

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
        PrivateDependencyModuleNames.AddRange(new string[] {"OnlineSubsystem", "OnlineSubsystemUtils", "OnlineSubsystemNull"});
        if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64))
        {
            if (UEBuildConfiguration.bCompileSteamOSS == true)
            {
                DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
            }
        }
	}
}
