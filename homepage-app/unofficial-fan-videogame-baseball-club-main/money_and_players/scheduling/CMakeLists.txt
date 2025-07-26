# MyAPMWProject/money_and_players/scheduling/CMakeLists.txt

# Create a standard library named 'scheduling_lib' from its source file.
add_library(scheduling_lib league_scheduler_2.cpp)

# Expose the current directory as a public include path for this library's
# header file (league_scheduler_2.h).
target_include_directories(scheduling_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# FIX v3.8.0: Explicitly link against the data library from the parent module.
# This is the correct way to inherit the necessary include paths.
target_link_libraries(scheduling_lib PRIVATE money_and_players_data)
