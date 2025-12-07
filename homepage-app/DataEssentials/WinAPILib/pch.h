#pragma once

// --- C++ Standard Library ---
#include <string> // Added to define std::string and std::wstring

// --- Public Interface ---
#include "CSVPrep_Interface.h"

// --- Windows & COM Headers ---
#define _WIN32_WINNT 0x0A00 // Target Windows 10 or later

#include <windows.h>
#include <shobjidl.h>
#include <KnownFolders.h>
#include <atlbase.h>

// --- Linker Dependencies ---
#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "Ole32.lib")