#pragma once

// Target Windows 10 or later
#define _WIN32_WINNT 0x0A00

// Windows & COM Headers
#include <windows.h>
#include <shobjidl.h>
#include <KnownFolders.h>
#include <shellapi.h> // For ShellExecuteW

// Standard C++ Libraries needed by the implementation
#include <string>

// Linker Dependencies
#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "Ole32.lib")
