# Root/AyurvedaProjectManagementWorld/CMakeLists.txt
cmake_minimum_required(VERSION 3.31) # Minimum CMake version
project(AyurvedaProjectManagementWorld VERSION 3.9.2 LANGUAGES CXX) # Project name and version

# Set the C++ standard for the entire project
set(CMAKE_CXX_STANDARD 23) # Using C++23 standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_HINT_PREFER_PATHS OFF) # Ensure strict standard compliance

# Add the primary project module.
add_subdirectory(money_and_players)

# Create the main executable with the new branding.
add_executable(apm_world_simulator main.cpp)

# Link the executable against the libraries created by the module.
target_link_libraries(apm_world_simulator PRIVATE
    money_and_players_lib 
)
