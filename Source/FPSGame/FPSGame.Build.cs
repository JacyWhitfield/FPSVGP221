using UnrealBuildTool;

public class FPSGame : ModuleRules
{
    public FPSGame(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "AIModule", // <-- This is crucial for AI-related classes
            "GameplayTasks",
            "NavigationSystem"
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
