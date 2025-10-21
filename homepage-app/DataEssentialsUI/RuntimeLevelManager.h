#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RuntimeLevelManager.generated.h"

UCLASS()
class DATAESSENTIALSUI_API URuntimeLevelManager : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Loads a new, blank level at runtime.
	 * @param WorldContextObject The world context, required by the engine to know which world to perform the action in.
	 * @param TemplateLevelName The name of the pre-made empty level asset to load (e.g., "L_BlankLevelTemplate").
	 */
	UFUNCTION(BlueprintCallable, Category = "Runtime Level Utilities", meta = (WorldContext = "WorldContextObject"))
	static void CreateNewBlankLevelAtRuntime(UObject* WorldContextObject, FName TemplateLevelName);
};

