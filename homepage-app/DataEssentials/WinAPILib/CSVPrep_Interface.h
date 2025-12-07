#pragma once

// This constant should be used by the calling application to size its buffers.
// It is defined to match the Windows MAX_PATH value (260).
#define MAX_PATH_C 260

// This enum is C-compatible, so it can be part of the public interface.
enum class DialogStatus {
    SUCCESS,
    CANCELLED,
    ERROR_OCCURRED
};

// C-style functions can only accept and return C-compatible types.
// We use extern "C" to ensure the function names are not mangled by the C++ compiler.
extern "C" {
    // Instead of returning a std::string, this function now writes the path into a buffer you provide.
    // It returns 'true' on success and 'false' on cancellation.
    bool OpenFileDialog_C(char* outPath, size_t bufferSize);

    // This function now returns only the status. The chosen path is written into the buffer.
    DialogStatus SaveFileDialogModern_C(const char* initial_filename, char* outPath, size_t bufferSize);
}