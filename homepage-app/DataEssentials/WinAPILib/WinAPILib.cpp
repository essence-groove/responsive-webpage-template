#include "pch.h"
#include "CSVPrep_Interface.h"

// --- Helper Functions (Internal to the DLL) ---
// This helper converts a C++ string to a C-style char buffer safely.
void copy_string_to_buffer(const std::string& source, char* dest, size_t dest_size) {
    if (dest && dest_size > 0) {
        // Use strncpy_s for safe copying, truncating if necessary.
        strncpy_s(dest, dest_size, source.c_str(), _TRUNCATE);
    }
}

// --- Public API Implementation ---
extern "C" {
    bool OpenFileDialog_C(char* outPath, size_t bufferSize) {
        // The internal logic remains the same, using C++ features.
        OPENFILENAMEA ofn;
        CHAR szFile[MAX_PATH] = { 0 };
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = NULL; // No owner window for a console app
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files\0*.*\0";
        ofn.nFilterIndex = 1;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        if (GetOpenFileNameA(&ofn) == TRUE) {
            // We just copy the result into the provided buffer before returning.
            copy_string_to_buffer(ofn.lpstrFile, outPath, bufferSize);
            return true;
        }
        return false; // User cancelled or an error occurred
    }

    DialogStatus SaveFileDialogModern_C(const char* initial_filename, char* outPath, size_t bufferSize) {
        // 1. Initialize COM
        HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
        if (FAILED(hr)) {
            return DialogStatus::ERROR_OCCURRED;
        }

        // 2. Create the Dialog Instance
        CComPtr<IFileSaveDialog> pFileSave;
        hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL, IID_IFileSaveDialog, reinterpret_cast<void**>(&pFileSave));
        if (FAILED(hr)) {
            CoUninitialize();
            return DialogStatus::ERROR_OCCURRED;
        }

        // 3. Configure the Dialog
        // Convert the narrow C-style string to a wide string for the COM interface
        wchar_t wide_filename[MAX_PATH];
        mbstowcs_s(NULL, wide_filename, initial_filename, MAX_PATH);
        pFileSave->SetFileName(wide_filename);

        pFileSave->SetTitle(L"Save Processed CSV File");
        COMDLG_FILTERSPEC fileTypes[] = { { L"CSV (Comma-separated values)", L"*.csv" }, { L"All Files", L"*.*" } };
        pFileSave->SetFileTypes(ARRAYSIZE(fileTypes), fileTypes);
        pFileSave->SetDefaultExtension(L"csv");
        pFileSave->SetOptions(FOS_OVERWRITEPROMPT);

        // 4. Show the Dialog
        hr = pFileSave->Show(NULL); // NULL for console app

        DialogStatus final_status = DialogStatus::ERROR_OCCURRED;

        // 5. Get the Result
        if (SUCCEEDED(hr)) {
            CComPtr<IShellItem> pItem;
            hr = pFileSave->GetResult(&pItem);
            if (SUCCEEDED(hr)) {
                PWSTR pszFilePath = nullptr;
                hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
                if (SUCCEEDED(hr)) {
                    // Convert the result back to a C++ std::string first...
                    std::wstring widePath(pszFilePath);
                    std::string narrowPath(widePath.begin(), widePath.end());
                    CoTaskMemFree(pszFilePath);
                    // ...then copy it to the output buffer.
                    copy_string_to_buffer(narrowPath, outPath, bufferSize);
                    final_status = DialogStatus::SUCCESS;
                }
            }
        }
        else if (hr == HRESULT_FROM_WIN32(ERROR_CANCELLED)) {
            final_status = DialogStatus::CANCELLED;
        }

        // 7. Uninitialize COM
        CoUninitialize();
        return final_status;
    }
}