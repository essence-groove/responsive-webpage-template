# Root/MyAPMWProject/CMakeLists.txt
cmake_minimum_required(VERSION 3.10) # Minimum CMake version
project(MyAPMWProject VERSION 3.5.0 LANGUAGES CXX) # Project name and version

# Set the C++ standard for the entire project
set(CMAKE_CXX_STANDARD 17) # Assuming a modern C++ standard for C++ 3.5.0 project version
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # Ensure strict standard compliance

# Add project modules (subdirectories)
# This processes the CMakeLists.txt in each respective directory
add_subdirectory(money_and_players)
add_subdirectory(scheduling)

# Create the main executable from main.cpp located at the root
add_executable(apmw_baseball_simulator main.cpp)

# Link the executable against the libraries created by the modules.
# CMake will automatically handle the include paths defined by the libraries.
target_link_libraries(apmw_baseball_simulator PRIVATE
    money_and_players_lib # Provides Player, Team, Game structures
    scheduling_lib        # Provides LeagueScheduler2 logic
)
