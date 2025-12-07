// WinAPILib.h - The public interface for our Windows API library.

#pragma once

// Standard headers needed for the interface
#include <string>
#include <filesystem>

// --- Public Interface ---
// These are the only functions the main application will be able to see.

enum class DialogStatus {
    SUCCESS,
    CANCELLED,
    ERROR_OCCURRED
};

struct DialogResult {
    std::string path;
    DialogStatus status;
};

// For static libraries, function declarations don't need import/export specifiers.
extern "C" std::string OpenFileDialog();
extern "C" DialogResult SaveFileDialogModern(const char* initial_filename);