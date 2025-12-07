#pragma once

// Target Windows 10 or later (implements your research point #3)
#define _WIN32_WINNT 0x0A00

// --- Standard C++ Libraries ---
#include <iostream>
#include <string>
#include <filesystem>
#include <regex>
#include <system_error>
#include <fstream>

// --- Windows & COM Headers (implements your research point #1) ---
#include <windows.h>
#include <shobjidl.h>    // For SHGetKnownFolderPath, FOLDERID constants
#include <KnownFolders.h> // Defines FOLDERID_RoamingAppData
#include <shellapi.h>     // For ShellExecuteW

// --- Linker Dependencies (implements your research point #2) ---
#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "Ole32.lib") // For CoTaskMemFree

// --- Project Interface ---
#include "CSVPrep_Interface.h"

