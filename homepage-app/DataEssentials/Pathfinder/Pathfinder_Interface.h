#pragma once

// This defines the buffer size that calling applications should use.
#define PATHFINDER_MAX_PATH 260

#ifdef PATHFINDER_EXPORTS
#define PATHFINDER_API __declspec(dllexport)
#else
#define PATHFINDER_API __declspec(dllimport)
#endif

// This C-style interface makes the DLL universally compatible.
extern "C" {
    // Gets the path to the user's AppData\Roaming folder.
    // Returns true on success, false on failure.
    PATHFINDER_API bool GetRoamingAppDataPath_C(char* outPath, size_t bufferSize);

    // Opens the specified folder path in Windows Explorer.
    PATHFINDER_API void OpenFolderInExplorer_C(const char* folderPath);
}
