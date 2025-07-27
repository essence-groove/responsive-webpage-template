# Root/MyAPMWProject/CMakeLists.txt
cmake_minimum_required(VERSION 3.31) # Minimum CMake version
project(MyAPMWProject VERSION 3.8.0 LANGUAGES CXX) # Project name and version

# Set the C++ standard for the entire project
set(CMAKE_CXX_STANDARD 23) # Using C++23 standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_HINT_PREFER_PATHS OFF) # Ensure strict standard compliance

# Add the top-level project module. This will now handle its own
# subdirectories, including the new nested 'scheduling' module.
add_subdirectory(money_and_players)

# Create the main executable. The orchestrator/scheduler logic is now
# part of a library, so it's no longer listed here.
add_executable(apmw_baseball_simulator main.cpp)

# Link the executable against the libraries created by the modules.
# We only need to link against the top-level library, and CMake will
# handle the transitive dependencies (like the scheduling logic).
target_link_libraries(apmw_baseball_simulator PRIVATE
    money_and_players_lib 
)
