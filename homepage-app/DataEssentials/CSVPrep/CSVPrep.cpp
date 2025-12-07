#include "pch.h"
#include "CSVPrep_Interface.h"

#pragma comment(lib, "WinAPILib.lib")

// --- SIMULATED FUNCTION ---
// This is a placeholder for the function that will eventually be in your Pathfinder library.
// It returns a hardcoded path, removing the need for any Windows API calls in this file.
std::filesystem::path get_roaming_appdata_path_simulated() {
    // We get the user's home directory path in a safe, standard way.
    char* user_profile_buffer = nullptr;
    size_t buffer_size = 0;
    if (_dupenv_s(&user_profile_buffer, &buffer_size, "USERPROFILE") == 0 && user_profile_buffer != nullptr) {
        std::filesystem::path user_profile(user_profile_buffer);
        free(user_profile_buffer);
        // Append the rest of the standard Roaming AppData path.
        return user_profile / "AppData" / "Roaming";
    }
    // Fallback in case the environment variable isn't found.
    return {};
}

int main() {
    // --- Step 1: Open File (No Change) ---
    char source_path_buffer[MAX_PATH_C] = { 0 };
    if (!OpenFileDialog_C(source_path_buffer, MAX_PATH_C)) {
        std::cout << "Operation cancelled.\n";
        return 0;
    }
    std::string source_file_path_str(source_path_buffer);
    std::filesystem::path source_path(source_file_path_str);

    // --- Step 2: Create a temporary working directory (No Change) ---
    char* appdata_buffer = nullptr;
    size_t buffer_size = 0;
    if (_dupenv_s(&appdata_buffer, &buffer_size, "LOCALAPPDATA") != 0 || appdata_buffer == nullptr) {
        std::cerr << "Error: Could not find AppData folder.\n";
        std::cin.get();
        return 1;
    }
    std::filesystem::path working_dir = std::filesystem::path(appdata_buffer) / "CSVPrep";
    free(appdata_buffer);
    std::filesystem::create_directories(working_dir);

    // --- Step 3: Process the file in the temporary directory (No Change) ---
    std::filesystem::path temp_source_path = working_dir / source_path.filename();
    try {
        std::filesystem::copy_file(source_path, temp_source_path, std::filesystem::copy_options::overwrite_existing);
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error copying file to temporary location: " << e.what() << "\n";
        std::cin.get();
        return 1;
    }
    std::string original_base_name = temp_source_path.stem().string();
    std::string sanitized_base_name = std::regex_replace(original_base_name, std::regex("[^a-zA-Z0-9_]"), "_");
    std::string new_csv_filename_str = sanitized_base_name + ".csv";
    std::filesystem::path processed_path = working_dir / new_csv_filename_str;
    try {
        std::filesystem::rename(temp_source_path, processed_path);
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error processing temporary file: " << e.what() << "\n";
        std::cin.get();
        return 1;
    }

    // --- Step 4: Create the final destination folder in RoamingAppData (NOW USES SIMULATED FUNCTION) ---
    auto appData = get_roaming_appdata_path_simulated();
    if (appData.empty()) {
        std::cerr << "Error: couldn't find Roaming AppData folder.\n";
        std::cin.get();
        return 1;
    }
    std::filesystem::path appFolder = appData / "DataEssentials";
    if (!std::filesystem::exists(appFolder)) {
        std::filesystem::create_directory(appFolder);
    }

    // --- Step 5: Move the processed file to its final destination (No Change) ---
    std::filesystem::path finalFilePath = appFolder / new_csv_filename_str;
    try {
        std::filesystem::rename(processed_path, finalFilePath);
        std::cout << "Successfully processed and saved file to:\n" << finalFilePath.string() << "\n\n";
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error moving file to final destination: " << e.what() << "\n";
        std::cin.get();
        return 1;
    }

    // --- Step 6: Help the User Find the File (No Change) ---
    std::cout << "Would you like to open the file's location? (y/n): ";
    char user_choice;
    std::cin >> user_choice;

    if (user_choice == 'y' || user_choice == 'Y') {
        // This still requires a Windows header, which we'll address by moving it to the DLL.
        // For now, we'll keep the dependency here until the final integration.
        ShellExecuteW(NULL, L"explore", appFolder.c_str(), NULL, NULL, SW_SHOWNORMAL);
    }

    std::cout << "\nProcess complete. Press Enter to exit.";
    std::cin.get(); // Consume the newline from the previous input
    std::cin.get(); // Wait for final Enter press
    return 0;
}

