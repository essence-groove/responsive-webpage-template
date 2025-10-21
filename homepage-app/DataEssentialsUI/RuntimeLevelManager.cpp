#include "RuntimeLevelManager.h"
#include "Kismet/GameplayStatics.h"

void URuntimeLevelManager::CreateNewBlankLevelAtRuntime(UObject* WorldContextObject, FName TemplateLevelName)
{
	if (!WorldContextObject)
	{
		UE_LOG(LogTemp, Error, TEXT("CreateNewBlankLevelAtRuntime was called with an invalid World Context."));
		return;
	}

	if (TemplateLevelName.IsNone())
	{
		UE_LOG(LogTemp, Warning, TEXT("CreateNewBlankLevelAtRuntime was called with an empty level name."));
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Attempting to load level by name: %s"), *TemplateLevelName.ToString());

	// This is the core engine function for changing levels in a packaged game.
	UGameplayStatics::OpenLevel(WorldContextObject, TemplateLevelName);
}

