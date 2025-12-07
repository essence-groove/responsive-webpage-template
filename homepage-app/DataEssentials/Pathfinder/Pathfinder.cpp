#include "pch.h"
#include "Pathfinder_Interface.h"
#include <iostream>

// This function gets the Roaming AppData path and writes it into the provided buffer.
bool GetRoamingAppDataPath_C(char* outPath, size_t bufferSize) {
    if (!outPath || bufferSize == 0) {
        return false;
    }

    PWSTR pszPath = nullptr;
    HRESULT hr = SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &pszPath);

    if (SUCCEEDED(hr)) {
        // Convert the wide string (UTF-16) from the API to a narrow string (UTF-8)
        size_t charsConverted = 0;
        wcstombs_s(&charsConverted, outPath, bufferSize, pszPath, bufferSize - 1);
        CoTaskMemFree(pszPath); // Free the memory!
        return true;
    }

    return false;
}

// This function opens a folder in Windows Explorer.
void OpenFolderInExplorer_C(const char* folderPath) {
    // Convert narrow string path to wide string for the API
    wchar_t widePath[PATHFINDER_MAX_PATH];
    size_t charsConverted = 0;
    mbstowcs_s(&charsConverted, widePath, PATHFINDER_MAX_PATH, folderPath, strlen(folderPath));

    ShellExecuteW(NULL, L"explore", widePath, NULL, NULL, SW_SHOWNORMAL);
}

// DllMain is the entry point for a DLL, required by the linker.
BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
